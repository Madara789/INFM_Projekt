
#include "Subspace.h"

Subspace::Subspace(
        int32_t signature,
        std::pair<DenseUnit, DenseUnit> denseUnits,
        std::vector<double> dimensions
        ) : signature(signature), denseUnits(denseUnits), dimensions(dimensions)
{}

int32_t Subspace::getSignature()
{
    return this->signature;
}

std::pair<DenseUnit, DenseUnit> Subspace::getDenseUnits()
{
    return this->denseUnits;
}


std::vector<double> Subspace::getDimensions()
{
    return this->dimensions;
}

void Subspace::addDimension(double dimension)
{
    this->dimensions.push_back(dimension);
}
