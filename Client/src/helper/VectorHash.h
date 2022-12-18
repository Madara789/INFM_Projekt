#pragma once

#include <vector>
#include <stdint.h>

namespace VectorHash {
	int hash(int nRounds, int rShift, int mulOp, const unsigned int key);
	int HashVector(std::vector<uint32_t> const& vec);
}
