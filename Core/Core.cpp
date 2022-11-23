#include "Core.h"
#include "Subscale/Factory/SequentialSubscaleFactory.h"
#include "Subscale/DataLabeler/SequentialDataLabeler.h"
#include "Helper/Config.h"

int main(int argc, char *argv[])
{
    auto config = Config::get();
    DataLabelerInterface* dataLabeler = new SequentialDataLabeler(config->getMinPoints(), config->getMinLabel(), config->getMaxLabel());
	ImporterInterface *importer = new CsvImporter("data/sample5.csv");
    auto tuple = importer->import(dataLabeler);
    delete importer;
    delete dataLabeler;

    SubscaleFactoryInterface* factory = new SequentialSubscaleFactory();
    Clusters clusters = factory->make().getClusters(std::get<0>(tuple), std::get<1>(tuple) , std::get<2>(tuple));
    delete factory;

	ExporterInterface *exporter = new CsvClusterExporter("result/cluster.csv", clusters);
	exporter->doExport();
    delete exporter;

	return 0;
}
