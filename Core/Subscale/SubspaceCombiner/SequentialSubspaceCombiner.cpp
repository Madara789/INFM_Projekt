#include "SequentialSubspaceCombiner.h"

#include "../Importer/Point.h"

#include <map>

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