#include "SubscaleSeq.h"

// calculates cluster candidates from given core sets
LocalSubspaceTable* SubscaleSeq::calculateCandidates(
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
	// create local host tables

	// dense unit table
	denseUnitTableWrapper = new LocalDenseUnitTable(config->minPoints, numberOfDimensions, duTableSize);

	// subspace table 1
	localSubspaceTable = new LocalSubspaceTable(numberOfPoints, numberOfDimensions, condensedSsTableSize);

	// subspace table 2
	subspaceTableWrapper = new LocalSubspaceTable(numberOfPoints, numberOfDimensions, ssTableSize);

	// subspace table 3 (same as 1 because one fewer table is needed when all tables are on host memory)
	condensedSsTableWrapper = localSubspaceTable;

	//
	// calculation classes
	DenseUnitCreatorSeq* denseUnitCreator = new DenseUnitCreatorSeq(denseUnitTableWrapper->getPtr(), duTableSize);
	SubspaceJoinerSeq* subspaceJoiner = new SubspaceJoinerSeq(subspaceTableWrapper->getPtr(), ssTableSize);
	TableManagerSeq* tableManager = new TableManagerSeq();

	// initialize
	denseUnitCreator->init(coreSets, labels, numberOfPoints, config->minPoints);
	subspaceJoiner->init(0);
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
		subspaceTableWrapper = new LocalSubspaceTable(numberOfPoints, numberOfDimensions, ssTableSize);
		subspaceJoiner = new SubspaceJoinerSeq(subspaceTableWrapper->getPtr(), ssTableSize);
		subspaceJoiner->init(0);

		//
		// combine slices
		numberOfEntries = combineAllSlices(subspaceJoiner, csvHandler, tableManager);

		// subspace table 5
		delete condensedSsTableWrapper;
		condensedSsTableWrapper = new LocalSubspaceTable(numberOfPoints, numberOfDimensions, numberOfEntries);

		tableManager->condenseTable(condensedSsTableWrapper->getPtr(), subspaceTableWrapper->getPtr(), ssTableSize);
		delete subspaceJoiner;
		delete subspaceTableWrapper;

	}

	// subspace table 6
	resultTable = new LocalSubspaceTable(numberOfPoints, numberOfDimensions, numberOfEntries);
	tableManager->localToLocal(resultTable, condensedSsTableWrapper->getPtr(), numberOfEntries);

	// free memory
	delete condensedSsTableWrapper;
	delete tableManager;
	timer.createTimestamp("Combination of slices");

	// write time differences to an output file
	std::string filePath = config->resultPath + "time_Subscale.txt";
	timer.writeTimestampDeltas(filePath.c_str());

	return resultTable;
}

LocalSubspaceTable* SubscaleSeq::getResultTable(CsvDataHandler* csvHandler, int numberOfDimensions,
	int numberOfPoints) {
	TableManagerSeq* tableManager = new TableManagerSeq();

	// subspace table 1
	localSubspaceTable = new LocalSubspaceTable(numberOfPoints, numberOfDimensions, condensedSsTableSize);

	// local host table for resulting candidates
	LocalSubspaceTable* resultTable;
	auto numberOfEntries = 0;

	if (config->splittingFactor > 1)
	{
		// if splitting factor is larger than 1, slices have to be read from the filesystem
		ssTableSize = roundToNextPrime(config->finalTableSize);

		// subspace table 4
		subspaceTableWrapper = new LocalSubspaceTable(numberOfPoints, numberOfDimensions, ssTableSize);
		auto subspaceJoiner = new SubspaceJoinerSeq(subspaceTableWrapper->getPtr(), ssTableSize);
		subspaceJoiner->init(0);

		//
		// combine slices
		auto numberOfEntries = combineAllSlices(subspaceJoiner, csvHandler, tableManager);

		// subspace table 5
		delete condensedSsTableWrapper;
		condensedSsTableWrapper = new LocalSubspaceTable(numberOfPoints, numberOfDimensions, numberOfEntries);

		tableManager->condenseTable(condensedSsTableWrapper->getPtr(), subspaceTableWrapper->getPtr(), ssTableSize);
		delete subspaceJoiner;
		delete subspaceTableWrapper;

	}

	// subspace table 6
	resultTable = new LocalSubspaceTable(numberOfPoints, numberOfDimensions, numberOfEntries);
	tableManager->localToLocal(resultTable, condensedSsTableWrapper->getPtr(), numberOfEntries);

	// free memory
	delete condensedSsTableWrapper;
	delete tableManager;

	return resultTable;
}

std::tuple<LocalSubspaceTable*, unsigned int> SubscaleSeq::calculateSlice(
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

	//
	// create local host tables

	// dense unit table
	denseUnitTableWrapper = new LocalDenseUnitTable(config->minPoints, numberOfDimensions, duTableSize);

	// subspace table 1
	localSubspaceTable = new LocalSubspaceTable(numberOfPoints, numberOfDimensions, condensedSsTableSize);

	// subspace table 2
	subspaceTableWrapper = new LocalSubspaceTable(numberOfPoints, numberOfDimensions, ssTableSize);

	// subspace table 3 (same as 1 because one fewer table is needed when all tables are on host memory)
	condensedSsTableWrapper = localSubspaceTable;

	//
	// calculation classes
	DenseUnitCreatorSeq* denseUnitCreator = new DenseUnitCreatorSeq(denseUnitTableWrapper->getPtr(), duTableSize);
	SubspaceJoinerSeq* subspaceJoiner = new SubspaceJoinerSeq(subspaceTableWrapper->getPtr(), ssTableSize);
	subspaceJoiner->init(0);
	TableManagerSeq* tableManager = new TableManagerSeq();

	// initialize
	denseUnitCreator->init(coreSets, labelsArray, numberOfPoints, config->minPoints);

	// create dense units
	denseUnitCreator->createDenseUnits(minSigBound, maxSigBound);

	// filter out all dense units that only appear in one dimension and copy dense units to a subspace table
	auto numberOfEntries = tableManager->duToSSTable(condensedSsTableWrapper->getPtr(), denseUnitTableWrapper->getPtr(), duTableSize);

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

	return { localSubspaceTable, numberOfEntries };
}