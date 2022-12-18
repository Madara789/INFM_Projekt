#include "Subscale.h"

#include "../TimeMeasurement/TimeMeasurement.h"

#define TICKET_SIZE 4

// calculates cluster candidates from given core sets
LocalSubspaceTable* Subscale::calculateCandidates(
	vector<vector<CoreSet>> coreSets,
	CsvDataHandler* csvHandler,
	unsigned long long* labels,
	int numberOfDimensions,
	int numberOfPoints,
	unsigned long long minSignature,
	unsigned long long maxSignature)
{
	unsigned int numberOfEntries = 0;

	// start timer
	TimeMeasurement timer;
	timer.start();

	//
	// create device tables

	// dense unit table
	denseUnitTableWrapper = new DeviceDenseUnitTable(config->minPoints, numberOfDimensions, duTableSize);

	// subspace table 1
	condensedSsTableWrapper = new DeviceSubspaceTable(numberOfPoints, numberOfDimensions, condensedSsTableSize);

	// subspace table 2
	subspaceTableWrapper = new DeviceSubspaceTable(numberOfPoints, numberOfDimensions, ssTableSize);

	// subspace table 3
	localSubspaceTable = new LocalSubspaceTable(numberOfPoints, numberOfDimensions, condensedSsTableSize);
	
	//
	// calculation classes
	DenseUnitCreator* denseUnitCreator = new DenseUnitCreator(denseUnitTableWrapper->getPtr(), duTableSize, config->threadsPerBlock, config->denseUnitsPerThread);
	SubspaceJoiner* subspaceJoiner = new SubspaceJoiner(subspaceTableWrapper->getPtr(), ssTableSize, config->threadsPerBlock);
	TableManager* tableManager = new TableManager(config->threadsPerBlock);

	// initialize
	denseUnitCreator->init(coreSets, labels, numberOfPoints, config->minPoints);
	subspaceJoiner->init(TICKET_SIZE);
	timer.createTimestamp("Initialisation");

	//
	// calculate slices
	numberOfEntries = calculateAllSlices(denseUnitCreator, subspaceJoiner, csvHandler, tableManager, minSignature, maxSignature);

	// free memory
	delete denseUnitCreator;
	delete denseUnitTableWrapper;
	delete subspaceJoiner;
	delete subspaceTableWrapper;
	delete[] labels;
	coreSets.erase(coreSets.begin(), coreSets.end());
	coreSets.shrink_to_fit();
	timer.createTimestamp("Calculation of Slices");

	// local host table for resulting candidates
	LocalSubspaceTable* resultTable;

	if (config->splittingFactor > 1)
	{
		// if splitting factor is larger than 1, slices have to be read from the filesystem
		ssTableSize = roundToNextPrime(config->finalTableSize);

		// subspace table 4
		subspaceTableWrapper = new DeviceSubspaceTable(numberOfPoints, numberOfDimensions, ssTableSize);
		subspaceJoiner = new SubspaceJoiner(subspaceTableWrapper->getPtr(), ssTableSize, config->threadsPerBlock);
		subspaceJoiner->init(TICKET_SIZE);

		//
		// combine slices
		numberOfEntries = combineAllSlices(subspaceJoiner, csvHandler, tableManager);
	
		// subspace table 5
		delete condensedSsTableWrapper;
		condensedSsTableWrapper = new DeviceSubspaceTable(numberOfPoints, numberOfDimensions, numberOfEntries);
	

		tableManager->condenseTable(condensedSsTableWrapper->getPtr(), subspaceTableWrapper->getPtr(), ssTableSize);
		delete subspaceJoiner;
		delete subspaceTableWrapper;

		// subspace table 6
		resultTable = new LocalSubspaceTable(numberOfPoints, numberOfDimensions, numberOfEntries);
		tableManager->deviceToLocal(resultTable, condensedSsTableWrapper->getPtr(), numberOfEntries);
	}
	else
	{
		// if splitting factor is 1, there is only 1 slice that is already in the host memory
		resultTable = new LocalSubspaceTable(numberOfPoints, numberOfDimensions, numberOfEntries);
		tableManager->localToLocal(resultTable, localSubspaceTable, numberOfEntries);
	}

	// free memory
	delete localSubspaceTable;
	delete condensedSsTableWrapper;
	delete tableManager;
	timer.createTimestamp("Combination of slices");

	// write time differences to an output file
	std::string filePath = config->resultPath + "time_Subscale.txt";
	timer.writeTimestampDeltas(filePath.c_str());

	return resultTable;
}

std::tuple<LocalSubspaceTable*, unsigned int> Subscale::calculateSlice(
	vector<vector<CoreSet>> coreSets,
	std::vector<unsigned long long>& labels,
	int numberOfDimensions,
	int numberOfPoints,
	unsigned long long minSigBound,
	unsigned long long maxSigBound) {

	auto labelsArray = new unsigned long long[labels.size()];

	for (size_t i = 0; i < labels.size(); i++)
	{
		labelsArray[i] = labels[i];
	}

	unsigned int numberOfEntries = 0;

	//
	// create device tables

	// dense unit table
	denseUnitTableWrapper = new DeviceDenseUnitTable(config->minPoints, numberOfDimensions, duTableSize);

	// subspace table 1
	condensedSsTableWrapper = new DeviceSubspaceTable(numberOfPoints, numberOfDimensions, condensedSsTableSize);

	// subspace table 2
	subspaceTableWrapper = new DeviceSubspaceTable(numberOfPoints, numberOfDimensions, ssTableSize);

	// subspace table 3
	localSubspaceTable = new LocalSubspaceTable(numberOfPoints, numberOfDimensions, condensedSsTableSize);

	//
	// calculation classes
	DenseUnitCreator* denseUnitCreator = new DenseUnitCreator(denseUnitTableWrapper->getPtr(), duTableSize, config->threadsPerBlock, config->denseUnitsPerThread);
	SubspaceJoiner* subspaceJoiner = new SubspaceJoiner(subspaceTableWrapper->getPtr(), ssTableSize, config->threadsPerBlock);
	TableManager* tableManager = new TableManager(config->threadsPerBlock);

	// initialize
	denseUnitCreator->init(coreSets, labelsArray, numberOfPoints, config->minPoints);
	subspaceJoiner->init(TICKET_SIZE);

	// create dense units
	denseUnitCreator->createDenseUnits(minSigBound, maxSigBound);

	// filter out all dense units that only appear in one dimension and copy dense units to a subspace table
	numberOfEntries = tableManager->duToSSTable(condensedSsTableWrapper->getPtr(), denseUnitTableWrapper->getPtr(), duTableSize);

	// check if slice is empty
	if (numberOfEntries > 0)
	{
		// join all entries by subspace
		subspaceJoiner->join(condensedSsTableWrapper->getPtr(), numberOfEntries);

		// condense table
		numberOfEntries = tableManager->condenseTable(condensedSsTableWrapper->getPtr(), subspaceTableWrapper->getPtr(), ssTableSize);

		// copy table to local memory
		tableManager->deviceToLocal(localSubspaceTable, condensedSsTableWrapper->getPtr(), numberOfEntries);
	}

	if (condensedSsTableWrapper != nullptr) {
		delete condensedSsTableWrapper;
	}

	if (subspaceTableWrapper != nullptr) {
		delete subspaceTableWrapper;
	}

	if (denseUnitCreator != nullptr) {
		delete denseUnitCreator;
	}

	if (subspaceJoiner != nullptr) {
		delete subspaceJoiner;
	}

	if (tableManager != nullptr) {
		delete tableManager;
	}

	if (labelsArray != nullptr) {
		delete[] labelsArray;
	}
	return { localSubspaceTable, numberOfEntries };
}





