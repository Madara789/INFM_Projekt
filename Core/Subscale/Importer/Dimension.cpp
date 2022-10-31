#include "Dimension.h"

#include <utility>

Dimension::Dimension(
	uint32_t id,
	Points points
) : id_(id),  points_(std::move(points)) {}


const Points &Dimension::getPoints() const
{
    return this->points_;
}

uint32_t Dimension::getId() const
{
    return this->id_;
}

std::ostream &operator<<(std::ostream &os, const Dimension &dimension)
{
    os << "id: " << dimension.id_ << "\n";
    for (auto point : dimension.points_)
    {
        os << *point;
    }
    os << "---------------------------------------\n";
    return os;
}
