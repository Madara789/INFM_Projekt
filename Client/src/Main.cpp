#include <iostream>
#include <CsvDataHandler/CsvDataHandler.h>
#include <SubscaleTypes.h>
#include <Subscale/Subscale.h>
#include <Subscale/SubscaleSeq.h>
#include <Clustering/Clustering.h>
#include <Remote/Remote.h>
#include <TimeMeasurement/TimeMeasurement.h>
#include <SubscaleConfig/SubscaleConfig.h>
#include <string>
#include <chrono>
#include <stdio.h>
#include <HelperFunctions/roundingFunctions.h>
#include <fstream>
#include <iostream>
#include "Config.h"
#include "remote/Client.h"
#include <entry/SubscaleEntry.h>
#include "helper/VectorHash.h"
#include <thread>
#include <mutex>
#include <generated/subscale.pb.h>

using subscale::RemoteSubspaceResponse;

int main(int argc, char *argv[])
{
    try
    {
        // Read config
        SubscaleConfig *config = new SubscaleConfig();
        config->readJson("SubscaleGPU/Config/config.json");
        config->splittingFactor = Client::Config::get()->getServers().size();

        // Handler for IO operations
        CsvDataHandler *csvHandler = new CsvDataHandler();

        // Read data points from a csv file
        vector<DataPoint> points;
        points = csvHandler->read(config->dataPath.c_str(), ',');

        // Shrink allocated memory of vector
        points.shrink_to_fit();

        const int numberOfDimensions = points[0].values.size();
        const int numberOfPoints = points.size();

        LabelGenerator *labelGenerator = new LabelGenerator(1e14, 2e14);

        // variables
        auto labels = std::vector<unsigned long long>();
        labels.reserve(numberOfPoints);
        unsigned long long minSignature;
        unsigned long long maxSignature;

        // generate labels
        labelGenerator->getLabelsForVector(labels, numberOfPoints);
        minSignature = labelGenerator->calcMinSignatureFromVector(labels, points.size(), config->minPoints);
        maxSignature = labelGenerator->calcMaxSignatureFromVector(labels, points.size(), config->minPoints);
        delete labelGenerator;

        auto minSigBounds = new unsigned long long[config->splittingFactor];
        auto maxSigBounds = new unsigned long long[config->splittingFactor];
        unsigned long long deltaSig = (maxSignature - minSignature) / config->splittingFactor;
        unsigned long long minSigBoundary = 0;
        unsigned long long maxSigBoundary = 0;

        for (int j = 0; j < config->splittingFactor; j++)
        {
            // calculate signaturary boundaries of current slice
            int i = (j + config->splittingFactor / 2) % config->splittingFactor;

            minSigBoundary = minSignature + i * deltaSig;

            if (i < config->splittingFactor - 1)
            {
                maxSigBoundary = minSigBoundary + deltaSig;
            }
            else
            {
                maxSigBoundary = maxSignature + 1;
            }

            minSigBounds[j] = minSigBoundary;
            maxSigBounds[j] = maxSigBoundary;
        }

        auto candidatesMap = std::map<int, SubscaleEntry *>();

        {
            auto tables = std::vector<RemoteSubspaceResponse>();
            tables.reserve(config->splittingFactor);

            auto servers = Client::Config::get()->getServers();
            std::vector<std::thread> workers;

            std::string addr = "ipv4:";
            for (size_t i = 0; i < servers.size() - 1; i++)
            {
                addr.append(servers[i]);
                addr.append(",");
            }
            addr.append(servers[servers.size() - 1]);

            std::mutex m;
            grpc::ChannelArguments args;
            args.SetLoadBalancingPolicyName("round_robin");
            for (auto i{0}; i < config->splittingFactor; ++i)
            {
                workers.emplace_back(std::thread([&](int index)
                                                 {
                Client::Client client{grpc::CreateCustomChannel(addr, grpc::InsecureChannelCredentials(), args)};
                auto result = client.remoteCalculation(labels, minSigBounds[index], maxSigBounds[index]);
                m.lock();
                tables.push_back(result);
                m.unlock();
                std::cout << "Table " << index << std::endl; },
                                                 i));
            }

            for (auto &worker : workers)
                worker.join();

            for (uint64_t i = 0; i < tables.size(); i++)
            {
                auto table = tables[i];

                auto tableSize = table.tablesize();

                for (auto &entry : table.entries())
                {
                    auto dimensionField = entry.dimensions();
                    auto idsField = entry.ids();

                    std::vector<uint32_t> dimensions(dimensionField.begin(), dimensionField.end());
                    std::vector<uint32_t> ids(idsField.begin(), idsField.end());

                    if (ids.size() == 0 || dimensions.size() == 0)
                        continue;

                    auto hashed = VectorHash::HashVector(dimensions);

                    auto it = candidatesMap.find(hashed);

                    if (it != candidatesMap.end())
                    {
                        // element found;
                        auto entry = it->second;
                        entry->mergeIds(ids);
                    }
                    else
                    {
                        auto entry = new SubscaleEntry(ids, dimensions);
                        candidatesMap.insert(std::make_pair(hashed, entry));
                    }
                }
            }
        }

        if (config->saveCandidates)
        {
            // Write cluster candidates to an output file
            auto resultFilePath = config->resultPath + "candidates.csv";
            csvHandler->writeCandidates(resultFilePath.c_str(), &candidatesMap);
        }

        if (config->useDBSCAN)
        {
            //
            // Search cluster candidates for real clusters with the DBSCAN algorithm
            Clustering* finalClustering = new Clustering(config->minPoints, config->epsilon);
            std::vector<Cluster> clusters = finalClustering->calculateClusters(points, &candidatesMap);

            if (config->saveClusters)
            {
                // Write clusters to an output file
                auto resultFilePath = config->resultPath + "clusters.csv";
                csvHandler->writeClusters(resultFilePath.c_str(), clusters);
            }
        }
    }
    catch (const std::exception &e)
    {
        // Error handling
        printf("Catch: %s\n", e.what());
        return -1;
    }
    return 0;
}