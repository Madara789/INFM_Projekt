#pragma once
#include "../Tables/LocalSubspaceTable.cuh"
#include "../Tables/TableManagerSeq.h"
#include "../DenseUnitCreator/DenseUnitCreatorSeq.h"
#include "../SubspaceJoiner/SubspaceJoinerSeq.h"
#include "../CsvDataHandler/CsvDataHandler.h"
#include "../SubscaleConfig/SubscaleConfig.h"
#include "ISubscale.h"



// Sequential subscale implementation
class SubscaleSeq : public ISubscale
{
private:

    LocalSubspaceTable* calculateCandidates(
        vector<vector<CoreSet>> coreSets,
        CsvDataHandler* csvHandler,
        unsigned long long* labels,
        int numberOfDimensions,
        int numberOfPoints,
        unsigned long long minSignature,
        unsigned long long maxSignature);

    std::tuple<LocalSubspaceTable*, unsigned int> calculateSlice(
        vector<vector<CoreSet>> coreSets,
        std::vector<unsigned long long>& labels,
        int numberOfDimensions,
        int numberOfPoints,
        unsigned long long minSigBound,
        unsigned long long maxSigBound);


public:
    SubscaleSeq(SubscaleConfig* config) : ISubscale(config)
    {}
};