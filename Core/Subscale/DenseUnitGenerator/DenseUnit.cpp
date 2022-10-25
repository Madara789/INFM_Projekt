#include "DenseUnit.h"

DenseUnit::DenseUnit(Points points, uint64_t signature, uint64_t dimension) {
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
