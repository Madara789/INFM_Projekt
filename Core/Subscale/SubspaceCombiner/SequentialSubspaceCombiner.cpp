#include "SequentialSubspaceCombiner.h"

#include "../Importer/Point.h"

#include <map>
#include <random>

Clusters SequentialSubspaceCombiner::getClusters(Subspaces subspaces) {
	Clusters clusters;

	for (Subspace subspace : subspaces) {
		std::map<uint64_t, Point*> points;
		for (DenseUnit denseUnit : subspace.getDenseUnits()) {
			for (Point* point : denseUnit.getPoints()) {
				if (points.find(point->getSignature()) == points.end()) {
					points[point->getSignature()] = point;
				}
			}
		}

		Points subspacePoints;
		for (auto it = points.begin(); it != points.end(); it++) {
			subspacePoints.push_back(it->second);
		}
		subspacePoints.shrink_to_fit();

		clusters.push_back(Cluster(subspace.getDimensions(), subspacePoints));
	}

	clusters.shrink_to_fit();

	return clusters;
}

Clusters SequentialSubspaceCombiner::createDummyClusters()
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
}