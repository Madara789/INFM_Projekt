#include "ClusterHelper.h"

namespace ClusterHelper
{

    void printCluster(Clusters &clusters)
    {
        for (auto &&cluster : clusters)
        {
            auto &&dimensions = cluster.getDimensions();

            std::cout << dimensions[0];

            for (uint32_t i = 1; i < dimensions.size(); i++)
            {
                std::cout << ", " << dimensions[i];
            }

            std::cout << " - ";

            auto &&points = cluster.getPoints();

            std::cout << points[0]->getSignature();

            for (uint32_t i = 1; i < points.size(); i++)
            {
                std::cout << ", " << points[i]->getSignature();
            }

            std::cout << std::endl;
        }
    }

    Clusters createDummyClusters()
    {
        Clusters clusters;

        for (size_t i = 0; i < 10; i++)
        {
            std::vector<uint32_t> ids;
            Points points;
            for (uint32_t j = 0; j < 5; j++)
            {
                for (uint32_t x = 0; x < 10; x++)
                {
                    std::random_device dev;
                    std::mt19937 rng(dev());
                    std::uniform_int_distribution<std::mt19937::result_type> dist1000(1, 1000); // distribution in range [1, 1000]
                    points.emplace_back(new Point(0, dist1000(rng)));
                }
                std::random_device dev;
                std::mt19937 rng(dev());
                std::uniform_int_distribution<std::mt19937::result_type> dist10000(1, 1000);
                ids.emplace_back(dist10000(rng));
            }

            clusters.emplace_back(Cluster(ids, points));
        }

        clusters.shrink_to_fit();

        return clusters;
    }
}