#ifndef SUBSCALE_SEQUENTIALDATALABELER_H
#define SUBSCALE_SEQUENTIALDATALABELER_H

#include <random>
#include <set>
#include "../DataLabelerInterface.h"
#include "../Importer/Dimension.h"

class SequentialDataLabeler: public DataLabelerInterface
{
private:
    int32_t minPoints_;
    uint64_t *labels_;
    uint64_t minLabel_;
    uint64_t maxLabel_;

    uint64_t calcMinSignature(int32_t numberOfLabels);
    uint64_t calcMaxSignature(int32_t numberOfLabels);
    std::set<uint64_t> fillWithFirstMinPoints();

public:
    SequentialDataLabeler(int minPoints, uint64_t minLabel, uint64_t maxLabel);
    std::tuple<uint64_t, uint64_t> label(const Dimensions& dimensions) override;
};

#endif //SUBSCALE_SEQUENTIALDATALABELER_H
