#include "SequentialSubscaleFactory.h"
#include "../DataLabeler/SequentialDataLabeler.h"
#include "../CoreSetGenerator/SequentialCoreSetGenerator.h"
#include "../DenseUnitGenerator/SequentialDenseUnitGenerator.h"

Subscale* SequentialSubscaleFactory::make() {
	return new Subscale(
		new SequentialDataLabeler(),
		new SequentialCoreSetGenerator(),
		new SequentialDenseUnitGenerator()
	);
}