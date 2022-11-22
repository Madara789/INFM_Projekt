#include "Point.h"

Point::Point(
	double_t value,
	uint64_t signature
) : value_(value), signature_(signature) {}

double_t Point::getValue() {
	return this->value_;
}

uint64_t Point::getSignature() {
	return this->signature_;
}

std::ostream &operator<<(std::ostream &os, const Point &point)
{
    os << "value_: " << point.value_ << " signature_: " << point.signature_ << "\n";
    return os;
}

void Point::setSignature(uint64_t signature)
{
    signature_ = signature;
}
