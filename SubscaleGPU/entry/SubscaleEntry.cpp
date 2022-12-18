#include "SubscaleEntry.h"

SubscaleEntry::SubscaleEntry(std::vector<uint32_t> ids, std::vector<uint32_t> dimensions) 
	: ids_(ids), dimensions_(dimensions)
{
}

std::vector<uint32_t> SubscaleEntry::getIds() {
	return ids_;
}

void SubscaleEntry::mergeIds(std::vector<uint32_t> ids) {
	for (auto id : ids)
	{
		auto inVector = false;

		for (auto entryId : ids_)
		{
			if (id == entryId) {
				inVector = true;
			}
		}

		if (!inVector) {
			ids_.push_back(id);
		}
	}
}

std::vector<uint32_t> SubscaleEntry::getDimensions() {
	return dimensions_;
}
