#include "SequentialSubscaleFactory.h"
#include "../DataLabeler/SequentialDataLabeler.h"
#include "../CoreSetSeeker/SequentialCoreSetSeeker.h"
#include "../DenseUnitGenerator/SequentialDenseUnitGenerator.h"
#include "../SubspaceDetector/SequentialSubspaceDetector.h"
#include "../SubspaceCombiner/SequentialSubspaceCombiner.h"
#include "../../Helper/Config.h"
#include "../DenseUnitCombiner/SequentialDenseUnitCombiner.h"

Subscale SequentialSubscaleFactory::make() {
    auto config = Config::get();
	return {
            new SequentialDataLabeler(config->getMinPoints(), config->getMinLabel(), config->getMaxLabel()),
		    new SequentialCoreSetGenerator(config->getMinPoints(), config->getEpsilon()),
            new SequentialDenseUnitGenerator(),
            new SequentialDenseUnitCombiner(),
            new SequentialSubspaceDetector(),
            new SequentialSubspaceCombiner()
            };
}