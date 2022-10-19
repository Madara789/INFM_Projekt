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

void DataSet::setMinSignature(unsigned long long newMinSignature) {
	this->minSignature_ = newMinSignature;
}

void DataSet::setMaxSignature(unsigned long long newMaxSignature) {
	this->maxSignature_ = newMaxSignature;
}

unsigned long long DataSet::getMinSignature() {
	return this->minSignature_;
}

unsigned long long DataSet::getMaxSignature() {
	return this->maxSignature_;
}