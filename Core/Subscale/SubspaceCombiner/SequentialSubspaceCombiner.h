#pragma once

#include "../SubspaceCombinerInterface.h"

class SequentialSubspaceCombiner : public SubspaceCombinerInterface {
public:
	Clusters getClusters(Subspaces subspaces) override;
	Clusters createDummyClusters() override;
};