LocalSubspaceTable* calculateSlice(...) {
	// dense unit table
	denseUnitTableWrapper = new LocalDenseUnitTable(config->minPoints, numberOfDimensions, duTableSize);
	// subspace table 1
	localSubspaceTable = new LocalSubspaceTable(numberOfPoints, numberOfDimensions, condensedSsTableSize);
	// subspace table 2
	subspaceTableWrapper = new LocalSubspaceTable(numberOfPoints, numberOfDimensions, ssTableSize);
	// subspace table 3 (same as 1 because one fewer table is needed when all tables are on host memory)
	condensedSsTableWrapper = localSubspaceTable;
	// calculation classes
	DenseUnitCreatorSeq* denseUnitCreator = new DenseUnitCreatorSeq(denseUnitTableWrapper->getPtr(), duTableSize);
	SubspaceJoinerSeq* subspaceJoiner = new SubspaceJoinerSeq(subspaceTableWrapper->getPtr(), ssTableSize);
	TableManagerSeq* tableManager = new TableManagerSeq();

    // [...]
}