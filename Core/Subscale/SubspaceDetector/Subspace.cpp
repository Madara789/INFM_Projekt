#include "Subspace.h"

Subspace::Subspace(const DenseUnit &denseUnit)
{
    dimensions_.push_back(denseUnit.getDimension());
    denseUnits_.push_back(denseUnit);
}

DenseUnits Subspace::getDenseUnits()
{
	return this->denseUnits_;
}

std::vector<uint32_t> Subspace::getDimensions()
{
	return this->dimensions_;
}

void Subspace::addDenseUnit(const DenseUnit &denseUnit)
{
    denseUnits_.push_back(denseUnit);
    dimensions_.push_back(denseUnit.getDimension());
}
