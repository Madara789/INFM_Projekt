#pragma once

#include <vector>
#include <stdint.h>

class SubscaleEntry
{
private:
	std::vector<uint32_t> ids_;
	std::vector<uint32_t> dimensions_;

public:
	SubscaleEntry(std::vector<uint32_t> ids, std::vector<uint32_t> dimensions);

	std::vector<uint32_t> getIds();
	void mergeIds(std::vector<uint32_t> ids);
	std::vector<uint32_t> getDimensions();
};
