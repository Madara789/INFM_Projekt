#include "Subscale.h"

#include <vector>
#include <iostream>
#include <chrono>
#include "Helper/Config.h"
#include "Subscale/Exporter/CsvDenseUnitExporter.h"

Subscale::Subscale(
        CoreSetSeekerInterface* coreSetSeeker,
        DenseUnitGeneratorInterface* denseUnitGenerator,
        DenseUnitCombinerInterface* denseUnitCombiner,
        SubspaceDetectorInterface* subspaceDetector,
        SubspaceCombinerInterface* subspaceCombiner
        ) : coreSetSeeker(coreSetSeeker), denseUnitGenerator(denseUnitGenerator), denseUnitCombiner(denseUnitCombiner) ,subspaceDetector(subspaceDetector), subspaceCombiner(subspaceCombiner)
{}

Clusters Subscale::getClusters(Dimensions& dimensions, uint64_t minSignature, uint64_t maxSignature) {
	std::vector<CoreSets> allCoreSets;
	for (const Dimension& dimension : dimensions) {
        allCoreSets.push_back(this->coreSetSeeker->getCoreSets(dimension));
    }
    delete this->coreSetSeeker;
    dimensions.clear();
    allCoreSets.shrink_to_fit();

    uint32_t slices = 0;
    uint32_t splittingFactor = Config::get()->getSplittingFactor();
    uint64_t deltaSig = (maxSignature - minSignature) / splittingFactor;
    for (uint32_t j = 0; j < splittingFactor; j++)
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        uint32_t i = (j + splittingFactor / 2) % splittingFactor;
        uint64_t minSigBoundary = minSignature + i * deltaSig;
        uint64_t maxSigBoundary = 0;

        if (i < splittingFactor - 1)
            maxSigBoundary = minSigBoundary + deltaSig;
        else
            maxSigBoundary = maxSignature + 1;

        auto denseUnitsOfSplit = this->denseUnitGenerator->getDenseUnits(allCoreSets, Config::get()->getMinPoints(), minSigBoundary, maxSigBoundary);

        std::stringstream s;
        s << "temp/slice-" << slices << ".csv";
        CsvDenseUnitExporter exporter(s.str(), *denseUnitsOfSplit);
        exporter.doExport();
        delete denseUnitsOfSplit;
        slices++;
        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - begin).count() << "s" << std::endl;
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