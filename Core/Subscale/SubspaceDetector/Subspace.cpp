#include "Subspace.h"

DenseUnits Subspace::getDenseUnits() {
	return this->denseUnits_;
}

std::vector<uint32_t> Subspace::getDimensions() {
	return this->dimensions_;
}