#pragma once
#include "../Tables/LocalSubspaceTable.cuh"
#include <iostream>
#include "../SubscaleConfig/SubscaleConfig.h"
#include "../CsvDataHandler/CsvDataHandler.h"
#include "../Subscale/Subscale.h"
#include "../Subscale/SubscaleSeq.h"

namespace Remote {
	std::tuple<LocalSubspaceTable*, unsigned int> calculateRemote(std::vector<unsigned long long> lables, unsigned long long min, unsigned long long max);
}
