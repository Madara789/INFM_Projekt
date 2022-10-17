#include "Subscale.h"

Subscale::Subscale(
	DataLabelerInterface* dataLabeler,
	CoreSetGeneratorInterface* coreSetGenerator,
	DenseUnitGeneratorInterface* denseUnitGenerator
) : dataLabeler_(dataLabeler), 
	coreSetGenerator_(coreSetGenerator), 
	denseUnitGenerator_(denseUnitGenerator) 
{}

Subscale::~Subscale() {
	delete this->dataLabeler_;
	delete this->coreSetGenerator_;
	delete this->denseUnitGenerator_;
}

std::vector<Cluster> Subscale::getClusters(DataSet data)
{
	DataSet labeldData = this->dataLabeler_->label(data);
	CoreSets coreSets = this->coreSetGenerator_->getCoreSets(labeldData);
	DenseUnits denseUnits = this->denseUnitGenerator_->getDenseUnits(coreSets);

	return {};
}