#include "DenseUnit.h"

DenseUnit::DenseUnit(Points points, uint64_t signature, uint32_t dimension) {
    this->points_ = points;
    this->signature_ = signature;
    this->dimension_ = dimension;
}

    Points DenseUnit::getPoints()
{
    return this->points_;
}

uint64_t DenseUnit::getSignature() const
{
    return signature_;
}

uint32_t DenseUnit::getDimension() const
{
    return dimension_;
}

std::ostream &operator<<(std::ostream &os, const DenseUnit &unit)
{
    os << "dimension: " << unit.dimension_ << "\n";
    os << "signature: " << unit.signature_ << "\n";
    for (auto point : unit.points_)
    {
        os << *point;
    }
    os << "---------------------------------------\n";
    return os;
}
