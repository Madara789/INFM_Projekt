#ifndef SUBSCALE_SUBSPACE_H
#define SUBSCALE_SUBSPACE_H

#include <vector>
#include "DenseUnit.h"

class Subspace
{
private:
    int32_t signature;
    std::pair<DenseUnit, DenseUnit> denseUnits;
    std::vector<double> dimensions;

public:
    Subspace(int32_t signature, std::pair<DenseUnit, DenseUnit> denseUnits, std::vector<double> dimensions);
    int32_t getSignature();
    std::pair<DenseUnit, DenseUnit> getDenseUnits();
    std::vector<double> getDimensions();
    void addDimension(double dimension);
};

typedef std::vector<Subspace> Subspaces;

#endif //SUBSCALE_SUBSPACE_H
