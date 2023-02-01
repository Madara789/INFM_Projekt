LocalSubspaceTable* calculateSlice(...) {
	// Vorbereitung (wird in den nächsten Sektionen gezeigt)
    auto numberOfEntries = 0;

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
    // Free Memory 
	return localSubspaceTable;
}