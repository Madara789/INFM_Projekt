#include "CoreSet.h"

CoreSet::CoreSet() {
	this->points_ = Points();
}

CoreSet::CoreSet(
	uint32_t dimension
): dimension_(dimension) {}

void CoreSet::addPoint(Point* point) {
	this->points_.push_back(point);
}

size_t CoreSet::getSize() {
	return this->points_.size();
}

uint32_t CoreSet::getDimension() const
{
    return dimension_;
}

const Points &CoreSet::getPoints() const
{
    return points_;
}

std::ostream &operator<<(std::ostream &os, const CoreSet &set)
{
    os << "dimension: " << set.dimension_ << "\n";
    os << "points: \n";
    for (auto point : set.points_)
    {
        os << *point;
    }
    os << "---------------------------------------\n";
    return os;
}
