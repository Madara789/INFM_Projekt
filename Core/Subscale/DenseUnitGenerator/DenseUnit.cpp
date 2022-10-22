#include "DenseUnit.h"

Points DenseUnit::getPoints() {
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
