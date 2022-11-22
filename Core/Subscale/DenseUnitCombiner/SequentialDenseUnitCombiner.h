#ifndef SUBSCALE_SEQUENTIALDENSEUNITCOMBINER_H
#define SUBSCALE_SEQUENTIALDENSEUNITCOMBINER_H

#include "../DenseUnitCombinerInterface.h"

class SequentialDenseUnitCombiner : public DenseUnitCombinerInterface
{
public:
    DenseUnits *getDenseUnits(uint32_t slices) override;
    ~SequentialDenseUnitCombiner() override = default;
};


#endif //SUBSCALE_SEQUENTIALDENSEUNITCOMBINER_H
