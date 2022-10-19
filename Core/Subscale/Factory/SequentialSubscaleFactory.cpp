#include "SequentialSubscaleFactory.h"
#include "../DataLabeler/SequentialDataLabeler.h"
#include "../CoreSetGenerator/SequentialCoreSetGenerator.h"
#include "../DenseUnitGenerator/SequentialDenseUnitGenerator.h"

Subscale* SequentialSubscaleFactory::make() {
	return new Subscale(
		new SequentialDataLabeler(10, 10, 10, 10), // TODO set correct values
		new SequentialCoreSetGenerator(),
		new SequentialDenseUnitGenerator()
	);
}