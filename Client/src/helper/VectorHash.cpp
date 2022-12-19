#include "VectorHash.h"

int VectorHash::HashVector(std::vector<uint32_t> const& vec) {
	auto hashed = 0;
	for (auto& i : vec) {
		hashed = hashed * 31 + hash(sizeof(uint32_t), 8, 0xE9D58A6B, i);
	}
	return hashed;
}

int VectorHash::hash(int nRounds, int rShift, int mulOp, const unsigned int key)
{
	auto x = key;
	for (int j = nRounds; j > 0; --j) {
		x = ((x >> rShift) ^ x) * mulOp + j;
	}
	return x;
}
