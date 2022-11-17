#include "SequentialSubscaleFactory.h"
#include "../DataLabeler/SequentialDataLabeler.h"
#include "../CoreSetSeeker/SequentialCoreSetSeeker.h"
#include "../DenseUnitGenerator/SequentialDenseUnitGenerator.h"
#include "../SubspaceDetector/SequentialSubspaceDetector.h"
#include "../SubspaceCombiner/SequentialSubspaceCombiner.h"

Subscale SequentialSubscaleFactory::make() {
	return {
            new SequentialDataLabeler(2, 1e14, 2e14), // TODO add through Config
		    new SequentialCoreSetGenerator(2, 0.5), // TODO add through Config
            new SequentialDenseUnitGenerator(),
            new SequentialSubspaceDetector(),
            new SequentialSubspaceCombiner()
            };
}