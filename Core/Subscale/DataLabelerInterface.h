#pragma once

#include "../Data/DataSet.h"

class DataLabelerInterface
{
public:
	virtual DataSet label(DataSet dataSet) = 0;
};