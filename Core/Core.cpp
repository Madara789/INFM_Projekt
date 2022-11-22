#include "Core.h"
#include "Subscale/Factory/SequentialSubscaleFactory.h"

int main(int argc, char *argv[])
{
	ImporterInterface *importer = new CsvImporter("data/sample5.csv");
    auto dimensions = importer->import();
    delete importer;

    SubscaleFactoryInterface* factory = new SequentialSubscaleFactory();
    Clusters clusters = factory->make().getClusters(dimensions);
    delete factory;

//	auto dummyClusters = ClusterHelper::createDummyClusters();
//	ClusterHelper::printCluster(dummyClusters);

	ExporterInterface *exporter = new CsvClusterExporter("result/cluster.csv", clusters);
	exporter->doExport();

	return 0;
}
