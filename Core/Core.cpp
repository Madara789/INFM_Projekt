#include "Core.h"

int main(int argc, char* argv[]) {
	ImporterInterface importer = CsvImporter();

	Clusters clusters = Subscale().getClusters(importer.import());

	return 0;
}