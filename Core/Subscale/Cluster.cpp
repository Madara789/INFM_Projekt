#include "Cluster.h"

Cluster::Cluster(
	std::vector<uint32_t> dimensions,
	Points points
) : dimensions_(dimensions), points_(points) {}

std::vector<uint32_t> Cluster::getDimensions() {
	return this->dimensions_;
}

Points Cluster::getPoints() {
	return this->points_;
}