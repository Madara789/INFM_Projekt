#include "SequentialSubscaleFactory.h"

Subscale SequentialSubscaleFactory::make() {
	return Subscale(
		SequentialCoreSetGenerator(2, 0.5),
		SequentialDenseUnitGenerator(),
		SequentialSubspaceDetector(),
		SequentialSubspaceCombiner()
	);
}