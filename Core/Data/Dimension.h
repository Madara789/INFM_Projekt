#pragma once

#include <vector>

class Dimension
{
private:
	std::vector<double> points_;

public:
	Dimension(std::vector<double> points);
	std::vector<double> getPoints();
	unsigned int getSize();
};

typedef std::vector<Dimension> Dimensions;