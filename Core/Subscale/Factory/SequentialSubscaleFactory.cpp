#include "SequentialSubscaleFactory.h"
#include "../CoreSetSeeker/SequentialCoreSetSeeker.h"
#include "../DenseUnitGenerator/SequentialDenseUnitGenerator.h"
#include "../SubspaceDetector/SequentialSubspaceDetector.h"
#include "../SubspaceCombiner/SequentialSubspaceCombiner.h"
#include "../../Helper/Config.h"

Subscale SequentialSubscaleFactory::make() {
    auto config = Config::get();
	return {
		    new SequentialCoreSetGenerator(config->getMinPoints(), config->getEpsilon()),
            new SequentialDenseUnitGenerator(),
            new SequentialSubspaceDetector(),
            new SequentialSubspaceCombiner()
            };
}