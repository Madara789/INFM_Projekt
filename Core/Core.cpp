#include "Core.h"
#include "Subscale/Factory/SequentialSubscaleFactory.h"

int main(int argc, char* argv[]) {
	ImporterInterface* importer = new CsvImporter();

	Clusters clusters = (new SequentialSubscaleFactory())->make().getClusters(importer->import());

	return 0;
}