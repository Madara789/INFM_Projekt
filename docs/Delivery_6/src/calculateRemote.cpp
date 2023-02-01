LocalSubspaceTable* calculateRemote(...) {
	SubscaleConfig* config = new SubscaleConfig();
	config->readJson("Config/config.json");
	ISubscale* subscale;
	if (config->runSequential) {
		subscale = new SubscaleSeq(config);
	} else {
		subscale = new Subscale(config);
	}
	return subscale->calculateClusterCandidatesRemote(lables, min, max);
}