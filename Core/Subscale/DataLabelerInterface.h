#ifndef SUBSCALE_DATALABELERINTERFACE_H
#define SUBSCALE_DATALABELERINTERFACE_H

#include <tuple>
#include "Importer/Dimension.h"

class DataLabelerInterface
{
public:
    /**
     * Return a Tuple of minSignature and maxSignature
     */
    virtual std::tuple<uint64_t, uint64_t> label(const Dimensions& dimensions) = 0;
};

#endif //SUBSCALE_DATALABELERINTERFACE_H
