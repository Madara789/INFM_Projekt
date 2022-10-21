#pragma once

#include "Importer/Point.h"

#include <vector>


class Cluster {
private:
	std::vector<uint32_t> dimensions_;
	Points points_;

public:
	Cluster(std::vector<uint32_t> dimensions, Points points);
	std::vector<uint32_t> getDimensions();
	Points getPoints();
};

typedef std::vector<Cluster> Clusters;