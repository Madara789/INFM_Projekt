#include "CoreSet.h"

CoreSet::CoreSet() {
	this->points_ = Points();
}

CoreSet::CoreSet(
	Points points
): points_(points) {}

void CoreSet::addPoint(Point* point) {
	this->points_.push_back(point);
}

int32_t CoreSet::getSize() {
	return this->points_.size();
}