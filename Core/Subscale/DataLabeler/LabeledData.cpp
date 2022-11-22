#include "LabeledData.h"

LabeledData::LabeledData(const uint64_t &minSignature, const uint64_t &maxSignature, uint64_t *labels) : minSignature(minSignature), maxSignature(maxSignature), labels(labels)
{}

uint64_t LabeledData::getMinSignature() const
{
    return minSignature;
}

uint64_t LabeledData::getMaxSignature() const
{
    return maxSignature;
}

uint64_t *LabeledData::getLabels() const
{
    return labels;
}
