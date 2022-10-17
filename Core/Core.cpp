#include "Core.h"

int main(int argc, char* argv[]) {
	// TODO: Read data
	DataSet data = DataSet({});

	SubscaleFactoryInterface* subscaleFactory = new SequentialSubscaleFactory();
	Subscale* subscale = subscaleFactory->make();
	
	Clusters cluster = subscale->getClusters(data);

	return 0;
}