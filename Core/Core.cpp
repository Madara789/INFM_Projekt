#include "Core.h"
#include "Subscale/Factory/SequentialSubscaleFactory.h"
#include <iostream>

int main(int argc, char *argv[])
{

	LabelGenerator *labelGenerator = new LabelGenerator(1e14, 2e14);

	ImporterInterface *importer = new CsvImporter("data/sample5.csv", labelGenerator);

	auto tuple = importer->import(3);

	auto dimensions = std::get<0>(tuple);
	auto minSignature = std::get<1>(tuple);
	auto maxSignature = std::get<2>(tuple);

	const auto splittingFactor = 5;

	auto minSigBounds = new unsigned long long[splittingFactor];
	auto maxSigBounds = new unsigned long long[splittingFactor];
	unsigned long long deltaSig = (maxSignature - minSignature) / splittingFactor;
	unsigned long long minSigBoundary = 0;
	unsigned long long maxSigBoundary = 0;

	for (int j = 0; j < splittingFactor; j++)
	{
		// calculate signaturary boundaries of current slice
		int i = (j + splittingFactor / 2) % splittingFactor;

		minSigBoundary = minSignature + i * deltaSig;

		if (i < splittingFactor - 1)
		{
			maxSigBoundary = minSigBoundary + deltaSig;
		}
		else
		{
			maxSigBoundary = maxSignature + 1;
		}

		minSigBounds[j] = minSigBoundary;
		maxSigBounds[j] = maxSigBoundary;
	}

	auto subspace = (new SequentialSubscaleFactory())->make().getSubspaceTable(dimensions, minSigBounds[0], maxSigBounds[0]);

	//	auto dummyClusters = ClusterHelper::createDummyClusters();
	//	ClusterHelper::printCluster(dummyClusters);
	return 0;
}
