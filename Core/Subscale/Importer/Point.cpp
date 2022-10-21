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