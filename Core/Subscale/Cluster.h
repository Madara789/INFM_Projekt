#pragma once

#include "Importer/Point.h"

#include <vector>
#include <ostream>


class Cluster {
private:
	std::vector<uint32_t> dimensions_;
	Points points_;

public:
	Cluster(std::vector<uint32_t> dimensions, Points points);
    [[nodiscard]] const std::vector<uint32_t> &getDimensions() const;
    [[nodiscard]] const Points &getPoints() const;
    friend std::ostream &operator<<(std::ostream &os, const Cluster &cluster);
};

typedef std::vector<Cluster> Clusters;