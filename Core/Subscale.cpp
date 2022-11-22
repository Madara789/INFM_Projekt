#include "Subscale.h"

#include <vector>
#include <iostream>
#include <chrono>
#include "Helper/Config.h"
#include "Subscale/Exporter/CsvDenseUnitExporter.h"

Subscale::Subscale(
        DataLabelerInterface* dataLabeler,
        CoreSetSeekerInterface* coreSetSeeker,
        DenseUnitGeneratorInterface* denseUnitGenerator,
        DenseUnitCombinerInterface* denseUnitCombiner,
        SubspaceDetectorInterface* subspaceDetector,
        SubspaceCombinerInterface* subspaceCombiner
        ) : dataLabeler(dataLabeler), coreSetSeeker(coreSetSeeker), denseUnitGenerator(denseUnitGenerator), denseUnitCombiner(denseUnitCombiner) ,subspaceDetector(subspaceDetector), subspaceCombiner(subspaceCombiner)
{}

Clusters Subscale::getClusters(Dimensions& dimensions) {
    auto labeledData = this->dataLabeler->label(dimensions);
    delete this->dataLabeler;

	std::vector<CoreSets> allCoreSets;
	for (const Dimension& dimension : dimensions) {
        allCoreSets.push_back(this->coreSetSeeker->getCoreSets(dimension));
    }
    delete this->coreSetSeeker;
    dimensions.clear();
    allCoreSets.shrink_to_fit();

    uint32_t slices = 0;
    uint32_t splittingFactor = Config::get()->getSplittingFactor();
    uint64_t deltaSig = (labeledData->getMaxSignature() - labeledData->getMinSignature()) / splittingFactor;
    for (uint32_t j = 0; j < splittingFactor; j++)
    {
        uint32_t i = (j + splittingFactor / 2) % splittingFactor;
        uint64_t minSigBoundary = labeledData->getMinSignature() + i * deltaSig;
        uint64_t maxSigBoundary = 0;

        if (i < splittingFactor - 1)
            maxSigBoundary = minSigBoundary + deltaSig;
        else
            maxSigBoundary = labeledData->getMaxSignature() + 1;

        auto denseUnitsOfSplit = this->denseUnitGenerator->getDenseUnits(allCoreSets, Config::get()->getMinPoints(), minSigBoundary, maxSigBoundary, labeledData->getLabels());

        std::stringstream s;
        s << "temp/slice-" << slices << ".csv";
        CsvDenseUnitExporter exporter(s.str(), *denseUnitsOfSplit);
        exporter.doExport();
        slices++;
    }
    delete this->denseUnitGenerator;
    allCoreSets.clear();

    auto denseUnits = this->denseUnitCombiner->getDenseUnits(slices);

	Subspaces subspaces = this->subspaceDetector->detectSubspaces(*denseUnits);
    denseUnits->clear();
    delete this->subspaceDetector;

    auto clusters = this->subspaceCombiner->getClusters(subspaces);
    subspaces.clear();
    delete this->subspaceCombiner;

	return clusters;
}