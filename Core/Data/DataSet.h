#pragma once

#include <vector>
#include "Dimension.h"

class DataSet
{
private:
	Dimensions dimensions_;

public:
	DataSet(Dimensions dimensions);
	Dimensions getDimensions();
	unsigned int getSize();
	unsigned int getDimensionSize();
};