#ifndef SUBSCALE_SEQUENTIALDATALABELER_H
#define SUBSCALE_SEQUENTIALDATALABELER_H

#include <random>
#include <set>

// class for generating labels
class LabelGenerator
{
private:
	std::random_device rd;
	std::mt19937_64 gen;
	std::uniform_real_distribution<double> dis;
	unsigned long long minLabel;
	unsigned long long maxLabel;
public:
	LabelGenerator(unsigned long long minLabel, unsigned long long maxLabel);
	void getLabels(unsigned long long* labels, int numberOfLabels);

	unsigned long long calcMinSignature(unsigned long long* labels, int numberOfLabels, int minPoints);
	unsigned long long calcMaxSignature(unsigned long long* labels, int numberOfLabels, int minPoints);

	void getLabelsForVector(std::vector<unsigned long long>& labels, int numberOfLabels);

	unsigned long long calcMinSignatureFromVector(std::vector<unsigned long long>& labels, int numberOfLabels, int minPoints);
	unsigned long long calcMaxSignatureFromVector(std::vector<unsigned long long>& labels, int numberOfLabels, int minPoints);

	unsigned long long getRandomLabel();
};

#endif //SUBSCALE_SEQUENTIALDATALABELER_H
