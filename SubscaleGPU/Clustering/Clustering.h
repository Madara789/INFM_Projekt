#pragma once
#include "../Tables/LocalSubspaceTable.cuh"
#include "../SubscaleTypes.h"
#include "../entry/SubscaleEntry.h"
#include <map>

// class for final clustering
class Clustering
{
private:
	int minPoints;
	double epsilon;

public:
	Clustering(int minPoints, double epsilon);

	std::vector<Cluster> calculateClusters(vector<DataPoint> points, LocalSubspaceTable* clusterCandidates);
	std::vector<Cluster> calculateClusters(vector<DataPoint> points, LocalSubspaceTable* clusterCandidates, unsigned int numberOfEntries);
	std::vector<Cluster> calculateClusters(vector<DataPoint> points, std::map<int, SubscaleEntry*> *candidates);
};

