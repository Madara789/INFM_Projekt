#include "Core.h"
#include "Subscale/Factory/SequentialSubscaleFactory.h"

int main(int argc, char* argv[]) {
	ImporterInterface* importer = new CsvImporter("C:\\Users\\ernst\\OneDrive\\Desktop\\sample5.csv");

	Clusters clusters = (new SequentialSubscaleFactory())->make().getClusters(importer->import());

	return 0;
}