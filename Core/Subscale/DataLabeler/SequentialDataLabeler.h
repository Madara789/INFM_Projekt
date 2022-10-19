#pragma once

#include <random>
#include <set>
#include "../DataLabelerInterface.h"

class SequentialDataLabeler : public DataLabelerInterface
{
private:
	std::random_device rd_;
	std::mt19937_64 gen_;
	std::uniform_real_distribution<double> dis_;
	int minPoints_;
	int numberOfLabels_;
	unsigned long long *labels_;
	unsigned long long minLabel_;
	unsigned long long maxLabel_;

	void setStandardMersenneTwisterEngineSeedWithRd(); // FIXME rename for better understanding
	void setGeneratorForUniformlyDistributedDoubles(); // FIXME rename for better understanding
	void generateLabels();
	unsigned long long getRandomLabel();
	unsigned long long calcMinSignature();
	unsigned long long calcMaxSignature();
	std::set<unsigned long long> fillWithFirstMinPoints();
	unsigned long long calcSignatureByAccumulatingAllLabels(std::set<unsigned long long> labels);

public:
	SequentialDataLabeler(int minPoints, int numberOfLabels, unsigned long long minLabel, unsigned long long maxLabel);
	DataSet	label(DataSet dataSet);
};
