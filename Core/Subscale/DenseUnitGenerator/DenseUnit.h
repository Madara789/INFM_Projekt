#pragma once

#include "../Importer/Point.h"

#include <vector>

class DenseUnit {
private:
	Points points_;

public:
	Points getPoints();
};

typedef std::vector<DenseUnit> DenseUnits;