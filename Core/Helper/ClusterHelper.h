#pragma once

#include "../Subscale/Cluster.h"
#include "../Subscale/Importer/Point.h"

#include <iostream>
#include <vector>
#include <random>

namespace ClusterHelper{
    void printCluster(Clusters &clusters);
    Clusters createDummyClusters();
}