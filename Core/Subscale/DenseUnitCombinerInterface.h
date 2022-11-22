#ifndef SUBSCALE_DENSEUNITCOMBINERINTERFACE_H
#define SUBSCALE_DENSEUNITCOMBINERINTERFACE_H

#include "DenseUnitGenerator/DenseUnit.h"

class DenseUnitCombinerInterface {
public:
    virtual DenseUnits *getDenseUnits(uint32_t slices) = 0;
    virtual ~DenseUnitCombinerInterface() = default;
};

#endif //SUBSCALE_DENSEUNITCOMBINERINTERFACE_H
