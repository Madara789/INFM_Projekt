#ifndef SUBSCALE_EXPORTERINTERFACE_H
#define SUBSCALE_EXPORTERINTERFACE_H

#include "Data/Subspace.h"
#include "Data/Cluster.h"

class ExporterInterface
{
public:
    virtual void exportSubspaceTable(const Subspace& subspace) = 0;
    virtual void exportVectorTable(const Subspace& subspace) = 0;
    virtual void exportClusters(const Cluster& cluster) = 0;
};

#endif //SUBSCALE_EXPORTERINTERFACE_H
