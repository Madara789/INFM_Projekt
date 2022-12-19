#include "Remote.h"

std::tuple<LocalSubspaceTable*, unsigned int> Remote::calculateRemote(std::vector<unsigned long long> lables, unsigned long long min, unsigned long long max) {

	// Read config
	SubscaleConfig* config = new SubscaleConfig();
	config->readJson("SubscaleGPU/Config/config.json");

	// Calculate cluster candidates with the SUBSCALE algorithm
	ISubscale* subscale;

	if (config->runSequential) 
	{
		subscale = new SubscaleSeq(config);
	}
	else
	{
		subscale = new Subscale(config);
	}


	return subscale->calculateClusterCandidatesRemote(lables, min, max);
}
