#include "Dimension.h"

Dimension::Dimension(
	uint32_t id,
	Points points
) : id_(id),  points_(points) {}

Point* Dimension::getPoint(uint32_t index) {
	return this->points_[index];
}

size_t Dimension::getSize() {
	return this->points_.size();
}

uint32_t Dimension::getID() {
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
