#include <generated/subscale.pb.h>
#include <generated/subscale.grpc.pb.h>
#include <grpc++/grpc++.h>
#include <iostream>
#include <memory>
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
#include <tuple>
#include <HelperFunctions/roundingFunctions.h>
#include <fstream>
#include <iostream>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using subscale::RemoteSubscaleRequest;
using subscale::RemoteSubspaceResponse;

class SubscaleClient {
public:
    SubscaleClient(std::shared_ptr<Channel> channel): _stub{subscale::SubscaleRoutes::NewStub(channel)} {}

    std::tuple<LocalSubspaceTable*, unsigned int> remoteCalculation(std::vector<unsigned long long> lables, unsigned long long min, unsigned long long max)
    {
        RemoteSubscaleRequest request;
        request.set_minsignature(min);
        request.set_maxsignature(max);

        for (auto label : lables)
        {
            request.add_labels(label);
        }

        RemoteSubspaceResponse response;
        ClientContext context;
        Status status;
        status = _stub->RemoteSubscale(&context, request, &response);

        if (status.ok())
        {
            LocalSubspaceTable* table = new LocalSubspaceTable(response.idssize(), response.dimensionssize(), response.tablesize());
            for (int i = 0; i < response.idssize(); ++i)
            {
                uint32_t id = response.ids(i);
                table->insertIds(&id, i);
            }

            for (int i = 0; i < response.dimensionssize(); ++i)
            {
                uint32_t dimension = response.dimensions(i);
                table->insertDimensions(&dimension, i);
            }
            std::cout << "OK" << std::endl;

            return std::make_tuple(table, response.id());
        }

        throw std::runtime_error("GRPC Request Failed");
    }

private:
    std::unique_ptr<subscale::SubscaleRoutes::Stub> _stub;
};

int main(int argc, char* argv[])
{
    try
    {
        // Read config
        SubscaleConfig* config = new SubscaleConfig();
        config->readJson("SubscaleGPU/Config/config.json");

        // Handler for IO operations
        CsvDataHandler* csvHandler = new CsvDataHandler();

        // Read data points from a csv file
        vector<DataPoint> points;
        points = csvHandler->read(config->dataPath.c_str(), ',');

        // Shrink allocated memory of vector
        points.shrink_to_fit();

        const int numberOfDimensions = points[0].values.size();
        const int numberOfPoints = points.size();

        LabelGenerator* labelGenerator = new LabelGenerator(1e14, 2e14);

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

        auto tables = std::vector<std::tuple<LocalSubspaceTable*, unsigned int>>();
        tables.reserve(config->splittingFactor);

        SubscaleClient client{grpc::CreateChannel({"localhost:2510"}, grpc::InsecureChannelCredentials())};
        for (auto i{ 0 }; i < config->splittingFactor; ++i) {
//            auto result = Remote::calculateRemote(labels, minSigBounds[i], maxSigBounds[i]);
            auto result = client.remoteCalculation(labels, minSigBounds[i], maxSigBounds[i]);
            tables.push_back(result);
            std::cout << "Table " << i << std::endl;
        }

        auto duTableSize = roundToNextPrime(config->denseUnitTableSize);
        auto ssTableSize = roundToNextPrime(config->subspaceTableSize);

        // local host table for resulting candidates
        LocalSubspaceTable* resultTable;

        TableManagerSeq* tableManager = new TableManagerSeq();

        // subspace table 4
        auto subspaceTableWrapper = new LocalSubspaceTable(numberOfPoints, numberOfDimensions, ssTableSize);
        auto subspaceJoiner = new SubspaceJoinerSeq(subspaceTableWrapper->getPtr(), ssTableSize);
        subspaceJoiner->init(0);

        for (uint64_t i = 0; i < tables.size(); i++)
        {
            auto tuple = tables[i];
            auto localSubspaceTable = std::get<0>(tuple);
            auto numberOfEntries = std::get<1>(tuple);

            subspaceJoiner->join(localSubspaceTable, numberOfEntries);
            delete localSubspaceTable;
        }

        // count number of candidates
        auto numberOfCandidates = tableManager->countEntries(subspaceTableWrapper->getPtr(), ssTableSize);

        std::cout << numberOfCandidates << std::endl;

        //std::string resultFilePath;

        if (true)
        {
            // Write cluster candidates to an output file
            auto resultFilePath = config->resultPath + "candidates.csv";
            csvHandler->writeVecTable(resultFilePath.c_str(), subspaceTableWrapper, numberOfCandidates);
        }

        if (config->useDBSCAN)
        {
            //
            // Search cluster candidates for real clusters with the DBSCAN algorithm
            Clustering* finalClustering = new Clustering(config->minPoints, config->epsilon);
            std::vector<Cluster> clusters = finalClustering->calculateClusters(points, subspaceTableWrapper, numberOfCandidates);

            if (config->saveClusters)
            {
                // Write clusters to an output file
                auto resultFilePath = config->resultPath + "clusters.csv";
                csvHandler->writeClusters(resultFilePath.c_str(), clusters);
            }
        }

        //// Write timestamp differences to an output file
        //resultFilePath = config->resultPath + "time_Complete.txt";
        //timer.writeTimestampDeltas(resultFilePath.c_str());
    }
    catch (const std::exception& e)
    {
        // Error handling
        printf("Catch: %s\n", e.what());
        return -1;
    }
    return 0;
}