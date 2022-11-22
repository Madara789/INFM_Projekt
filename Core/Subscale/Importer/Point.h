#pragma once

#include <vector>
#include <cmath>
#include <cstdint>
#include <ostream>

class Point {
private:
	double_t value_;
	uint64_t signature_;

public:
	Point(double_t value, uint64_t signature);
	double_t getValue();
	uint64_t getSignature();
    void setSignature(uint64_t signature);
    friend std::ostream &operator<<(std::ostream &os, const Point &point);
};

typedef std::vector<Point*> Points;