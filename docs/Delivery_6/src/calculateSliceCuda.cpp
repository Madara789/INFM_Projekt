LocalSubspaceTable* calculateSlice(...) {
	// dense unit table
	denseUnitTableWrapper = new DeviceDenseUnitTable(config->minPoints, numberOfDimensions, duTableSize);
	// subspace table 1
	condensedSsTableWrapper = new DeviceSubspaceTable(numberOfPoints, numberOfDimensions, condensedSsTableSize);
	// subspace table 2
	subspaceTableWrapper = new DeviceSubspaceTable(numberOfPoints, numberOfDimensions, ssTableSize);
	// subspace table 3
	localSubspaceTable = new LocalSubspaceTable(numberOfPoints, numberOfDimensions, condensedSsTableSize);
	DenseUnitCreator* denseUnitCreator = new DenseUnitCreator(denseUnitTableWrapper->getPtr(), duTableSize, config->threadsPerBlock, config->denseUnitsPerThread);
	SubspaceJoiner* subspaceJoiner = new SubspaceJoiner(subspaceTableWrapper->getPtr(), ssTableSize, config->threadsPerBlock);
	TableManager* tableManager = new TableManager(config->threadsPerBlock);
    // [...]
}