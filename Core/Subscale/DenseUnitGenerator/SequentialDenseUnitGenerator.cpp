#include <iostream>
#include "SequentialDenseUnitGenerator.h"

DenseUnits *SequentialDenseUnitGenerator::getDenseUnits(const std::vector<CoreSets>& coreSets, uint32_t minPoints, uint64_t minSigBoundary, uint64_t maxSigBoundary)
{
    auto denseUnits = new DenseUnits();
    auto* combs = new uint64_t[3];
    for (const auto& coreSetOfDimension : coreSets) {
        for (const auto& coreSet : coreSetOfDimension)
        {
            uint64_t possibleCombinations = choose(coreSet.getPoints().size(), minPoints);
            uint32_t countCombs = 0;
            for (uint64_t i = 0; i <= possibleCombinations; ++i)
            {
                elements(i, coreSet.getPoints().size(), minPoints, combs);

                uint64_t signature = 0;
                for (uint32_t j = 0; j < minPoints; ++j)
                    signature += coreSet.getPoints()[combs[j]]->getSignature();

                if (signature >= minSigBoundary && signature < maxSigBoundary)
                {
                    Points pCombs;
                    for (uint32_t j = 0; j < minPoints; ++j)
                    {
                        pCombs.push_back(coreSet.getPoints()[combs[j]]);
                    }
                    denseUnits->push_back(DenseUnit(pCombs, signature, coreSet.getDimension()));
                }
                countCombs++;
            }
        }
    }

    delete[] combs;
    return denseUnits;
}

uint64_t SequentialDenseUnitGenerator::choose(uint64_t n, uint64_t k)
{
    if (n < k)
        return 0;

    if (n == k)
        return 1;

    uint64_t delta, iMax;

    if (k < (n - k))
    {
        delta = n - k;
        iMax = k;
    } else
    {
        delta = k;
        iMax = n - k;
    }

    uint64_t ans = delta + 1;
    for (uint64_t i = 2; i <= iMax; ++i)
        ans = (ans * (delta + i)) / i;

    return ans;
}

uint64_t SequentialDenseUnitGenerator::largestV(uint64_t a, uint64_t b, uint64_t x)
{
    uint64_t v = a - 1;
    while (choose(v, b) > x)
        --v;
    return v;
}

void SequentialDenseUnitGenerator::elements(uint64_t m, uint64_t n, uint64_t k, uint64_t* ans)
{
    uint64_t maxM = choose(n, k) - 1;

    uint64_t a = n;
    uint64_t b = k;
    uint64_t x = maxM - m;
    for (uint64_t i = 0; i < k; ++i)
    {
        ans[i] = largestV(a, b, x);
        x = x - choose(ans[i], b);
        a = ans[i];
        b = b - 1;
    }

    for (uint64_t i = 0; i < k; ++i)
        ans[i] = (n - 1) - ans[i];
}
