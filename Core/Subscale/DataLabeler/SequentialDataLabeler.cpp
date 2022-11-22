#include <iostream>
#include "SequentialDataLabeler.h"

SequentialDataLabeler::SequentialDataLabeler(int32_t minPoints, uint64_t minLabel, uint64_t maxLabel)
{
    this->minLabel_ = minLabel;
    this->maxLabel_ = maxLabel;
    this->minPoints_ = minPoints;
}

LabeledData *SequentialDataLabeler::label(const Dimensions &dimensions)
{
    int32_t numberOfLabels = dimensions.begin()->getPoints().size();
    labels_ = new uint64_t[numberOfLabels];
    std::random_device rd;
    auto gen = std::mt19937_64(rd());
    auto dis = std::uniform_real_distribution<double>(0, 1);
    for (int i = 0; i < numberOfLabels; i++)
    {
        labels_[i] = minLabel_ + dis(gen) * (maxLabel_ - minLabel_);
    }

    return new LabeledData(calcMinSignature(numberOfLabels), calcMaxSignature(numberOfLabels), labels_);
}

uint64_t SequentialDataLabeler::calcMinSignature(int32_t numberOfLabels)
{
    std::set<uint64_t> minLabels;

    minLabels = fillWithFirstMinPoints();

    for (int i = minPoints_; i < numberOfLabels; i++)
    {
        bool labelSmallerThanGreatestMinLabel = labels_[i] < *(--minLabels.end());
        if (labelSmallerThanGreatestMinLabel)
        {
            bool minLabelNotContainsLabel = minLabels.count(labels_[i]) == 0;
            if (minLabelNotContainsLabel)
            {
                minLabels.erase(--minLabels.end());
                minLabels.insert(labels_[i]);
            }
        }
    }

    uint64_t minSignature = 0;
    for (uint64_t label : minLabels)
    {
        minSignature += label;
    }

    return minSignature;
}

uint64_t SequentialDataLabeler::calcMaxSignature(int32_t numberOfLabels)
{
    std::set<uint64_t> maxLabels;

    maxLabels = fillWithFirstMinPoints();

    for (int i = minPoints_; i < numberOfLabels; i++)
    {
        bool labelGreaterThanSmallestMaxLabel = labels_[i] > *(maxLabels.begin());
        if (labelGreaterThanSmallestMaxLabel)
        {
            bool maxLabelNotContainsLabel = maxLabels.count(labels_[i]) == 0;
            if (maxLabelNotContainsLabel)
            {
                maxLabels.erase(maxLabels.begin());
                maxLabels.insert(labels_[i]);
            }
        }
    }

    uint64_t maxSignature = 0;
    for (uint64_t label : maxLabels)
    {
        maxSignature += label;
    }

    return maxSignature;
}

std::set<uint64_t> SequentialDataLabeler::fillWithFirstMinPoints()
{
    std::set<uint64_t> minLabels;

    for (int i = 0; i < minPoints_; i++)
    {
        minLabels.insert(labels_[i]);
    }

    return minLabels;
}
