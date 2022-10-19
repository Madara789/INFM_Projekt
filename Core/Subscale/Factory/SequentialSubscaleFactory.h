#pragma once

#include "../SubscaleFactoryInterface.h"
#include "../CoreSetSeeker/SequentialCoreSetSeeker.h"
#include "../DenseUnitGenerator/SequentialDenseUnitGenerator.h"
#include "../SubspaceDetector/SequentialSubspaceDetector.h"
#include "../SubspaceCombiner/SequentialSubspaceCombiner.h"

class SequentialSubscaleFactory : public SubscaleFactoryInterface
{
public:
	Subscale make();
};