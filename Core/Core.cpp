#include "Core.h"
#include "Subscale/Factory/SequentialSubscaleFactory.h"

#include <iostream>
#include <filesystem>

int main(int argc, char* argv[]) {


	ImporterInterface* importer = new CsvImporter("data/sample5.csv");

	//Clusters clusters = (new SequentialSubscaleFactory())->make().getClusters(importer->import());
	Clusters dummyClusters = (new SequentialSubscaleFactory())->make().createDummyClusters();
	
	ExporterInterface* exporter = new CsvClusterExporter("result/cluster.csv", dummyClusters);

	exporter->doExport();

	return 0;
}

void printCluster(Clusters& clusters){
		for (auto &&cluster : clusters)
	{
		auto &&dimensions = cluster.getDimensions();

		std::cout << dimensions[0];

		for (uint32_t i = 1; i < dimensions.size(); i++)
		{
			std::cout << ", " << dimensions[i];
		}

		std::cout << " - ";

		auto && points = cluster.getPoints(); 

		std::cout << points[0]->getSignature();

		for (uint32_t i = 1; i < points.size(); i++)
		{
			std::cout << ", " << points[i]->getSignature();
		}		
		
		std::cout << std::endl;
	}
}