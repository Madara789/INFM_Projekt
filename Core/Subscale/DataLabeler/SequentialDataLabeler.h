#pragma once

#include "../DataLabelerInterface.h"

class SequentialDataLabeler : public DataLabelerInterface
{
public:
	DataSet label(DataSet dataSet);
};