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

std::ostream &operator<<(std::ostream &os, const Cluster &cluster)
{
    for (auto dimension : cluster.dimensions_)
    {
        os << dimension;
    }

    for (auto point : cluster.points_)
    {
        os << point;
    }

    os << "---------------------------------------\n";
    return os;
}
