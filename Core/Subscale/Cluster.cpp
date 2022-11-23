#include "Cluster.h"

#include <utility>

Cluster::Cluster(
	std::vector<uint32_t> dimensions,
	Points points
) : dimensions_(std::move(dimensions)), points_(std::move(points)) {}

const std::vector<uint32_t> &Cluster::getDimensions() const
{
    return dimensions_;
}

const Points &Cluster::getPoints() const
{
    return points_;
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
