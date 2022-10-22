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