LocalSubspaceTable* calculateClusterCandidatesRemote(...) {
	CsvDataHandler* csvDataHandler = new CsvDataHandler();
	auto points = csvDataHandler->read(config->dataPath.c_str(), ',');
	delete csvDataHandler;

	auto numberOfDimensions = points[0].values.size();
	// Shrink allocated memory of vector
	points.shrink_to_fit();
	CoreSetCreator* coreSetCreator = new CoreSetCreator();
	// generate core sets
	auto coreSets = coreSetCreator->createCoreSets(points, config->minPoints, config->epsilon);
	delete coreSetCreator;

	auto result = calculateSlice(coreSets, lables, numberOfDimensions, points.size(), min, max);

	return result;
}