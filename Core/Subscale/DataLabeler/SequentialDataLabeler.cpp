#include "SequentialDataLabeler.h"

SequentialDataLabeler::SequentialDataLabeler(int minPoints, int numberOfLabels, unsigned long long minLabel, unsigned long long maxLabel)
{
	this->minLabel_ = minLabel;
	this->maxLabel_ = maxLabel;
	this->minPoints_ = minPoints;
	this->numberOfLabels_ = numberOfLabels;

	setStandardMersenneTwisterEngineSeedWithRd();
	setGeneratorForUniformlyDistributedDoubles();
}

DataSet SequentialDataLabeler::label(DataSet data)
{
	generateLabels();

	data.setMinSignature(calcMinSignature());
	data.setMaxSignature(calcMaxSignature());

	return data;
}

unsigned long long SequentialDataLabeler::calcMinSignature()
{
	unsigned long long minSignature;
	std::set<unsigned long long> minLabels;

	minLabels = fillWithFirstMinPoints();

	for (int i = minPoints_; i < numberOfLabels_; i++) // FIXME outsource new function
	{ 
		bool labelSmallerThanGreatestMinLabel = labels_[i] < *(--minLabels.end());
		if (labelSmallerThanGreatestMinLabel)
		{
			bool minLabelNotContainsLabel = minLabels.count(labels_[i]) == 0;
			if (minLabelNotContainsLabel)
			{
				minLabels.erase(--minLabels.end());
				minLabels.insert(labels_[i]);
			}
		}
	}

	minSignature = calcSignatureByAccumulatingAllLabels(minLabels);

	return minSignature;
}

unsigned long long SequentialDataLabeler::calcSignatureByAccumulatingAllLabels(std::set<unsigned long long> labels)
{
	unsigned long long minSignature = 0;
	for (unsigned long long label : labels)
	{
		minSignature += label;
	}
	return minSignature;
}

unsigned long long SequentialDataLabeler::calcMaxSignature()
{
	unsigned long long maxSignature;
	std::set<unsigned long long> maxLabels;

	maxLabels = fillWithFirstMinPoints();

	for (int i = minPoints_; i < numberOfLabels_; i++) // FIXME outsource new function
	{
		bool labelGreaterThanSmallestMaxLabel = labels_[i] > *(maxLabels.begin());
		if (labelGreaterThanSmallestMaxLabel)
		{
			bool maxLabelNotContainsLabel = maxLabels.count(labels_[i]) == 0;
			if (maxLabelNotContainsLabel)
			{
				maxLabels.erase(maxLabels.begin());
				maxLabels.insert(labels_[i]);
			}
		}
	}

	maxSignature = calcSignatureByAccumulatingAllLabels(maxLabels);

	return maxSignature;
}

std::set<unsigned long long> SequentialDataLabeler::fillWithFirstMinPoints()
{
	std::set<unsigned long long> minLabels;

	for (int i = 0; i < minPoints_; i++)
	{
		minLabels.insert(labels_[i]);
	}

	return minLabels;
}

void SequentialDataLabeler::generateLabels()
{
	labels_ = new unsigned long long[numberOfLabels_];
	for (int i = 0; i < numberOfLabels_; i++)
	{
		labels_[i] = getRandomLabel();
	}
}

unsigned long long SequentialDataLabeler::getRandomLabel()
{
	return minLabel_ + dis_(gen_) * (maxLabel_ - minLabel_);
}

void SequentialDataLabeler::setStandardMersenneTwisterEngineSeedWithRd()
{
	gen_ = std::mt19937_64(rd_());
}

void SequentialDataLabeler::setGeneratorForUniformlyDistributedDoubles()
{
	dis_ = std::uniform_real_distribution<double>(0, 1);
}