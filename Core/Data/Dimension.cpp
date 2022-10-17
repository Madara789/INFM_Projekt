#include "Dimension.h"

Dimension::Dimension(
	std::vector<double> points
) : points_(points) {}

std::vector<double> Dimension::getPoints() {
	return this->points_;
}

unsigned int Dimension::getSize() {
	return this->points_.size();
}