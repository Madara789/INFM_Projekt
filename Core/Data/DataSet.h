#pragma once

#include <vector>
#include "Dimension.h"

class DataSet
{
private:
	Dimensions dimensions_;
	unsigned long long minSignature_;
	unsigned long long maxSignature_;

public:
	DataSet(Dimensions dimensions);
	Dimensions getDimensions();
	unsigned int getSize();
	unsigned int getDimensionSize();
	void setMinSignature(unsigned long long newMinSignature);
	void setMaxSignature(unsigned long long newMaxSignature);
	unsigned long long getMinSignature();
	unsigned long long getMaxSignature();
};