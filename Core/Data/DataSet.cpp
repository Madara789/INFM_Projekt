#include "DataSet.h"

DataSet::DataSet(
	Dimensions dimensions
) : dimensions_(dimensions) {}

Dimensions DataSet::getDimensions() {
	return this->dimensions_;
}

unsigned int DataSet::getSize() {
	return this->dimensions_.size();
}

unsigned int DataSet::getDimensionSize() {
	return this->dimensions_[0].getSize();
}