#pragma once

#include <vector>

class Point {
private:
	double_t value_;
	uint64_t signature_;

public:
	Point(double_t value, uint64_t signature);
	double_t getValue();
};

typedef std::vector<Point*> Points;