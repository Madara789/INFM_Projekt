#include "SequentialSubscaleFactory.h"

Subscale SequentialSubscaleFactory::make() {
	return Subscale(
		new SequentialCoreSetGenerator(2, 0.5),
        new SequentialDenseUnitGenerator(),
        new SequentialSubspaceDetector(),
        new SequentialSubspaceCombiner()
	);
}