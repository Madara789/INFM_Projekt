#include "Dimension.h"

Dimension::Dimension(
	Points points
) : points_(points) {}

Point* Dimension::getPoint(uint32_t index) {
	return this->points_[index];
}

uint32_t Dimension::getSize() {
	return this->points_.size();
}