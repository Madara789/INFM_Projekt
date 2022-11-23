#ifndef SUBSCALE_DATALABELERINTERFACE_H
#define SUBSCALE_DATALABELERINTERFACE_H

#include <tuple>
#include "Importer/Dimension.h"
#include "DataLabeler/LabeledData.h"

class DataLabelerInterface
{
public:
    virtual LabeledData *label(uint64_t numberOfLabels) = 0;
    virtual ~DataLabelerInterface() = default;
};

#endif //SUBSCALE_DATALABELERINTERFACE_H
