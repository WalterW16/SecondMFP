#include "NumberSequenceGenerator.h"

NumberSequenceGenerator::NumberSequenceGenerator(std::vector<VeryLong> NewSequence)
{
	sequence = NewSequence;
}

NumberSequenceGenerator::NumberSequenceGenerator(const NumberSequenceGenerator& other)
{
	this->sequence = other.sequence;
}

void NumberSequenceGenerator::GenerateArithmeticProgression(VeryLong firstTerm, VeryLong CommonDifference, int n)
{
	sequence.clear();	
	for (int i=0; i<n; ++i) {
		sequence.push_back(firstTerm);
		firstTerm += CommonDifference;		
	}
}

void NumberSequenceGenerator::GenerateGeometricProgression(VeryLong firstTerm , VeryLong commonRatio, int n)
{
	sequence.clear();
	for (int i = 0; i < n; ++i) {
		sequence.push_back(firstTerm);
		firstTerm *= commonRatio;
	}
}



int NumberSequenceGenerator::countPrimaryNumbers()
{
	std::vector<VeryLong> ::iterator itb = sequence.begin();
	std::vector<VeryLong> ::iterator ite = sequence.end();
	return std::count_if(itb, ite, IsPrimary);
}



int NumberSequenceGenerator::countEvenNumbers()
{
	std::vector<VeryLong> ::iterator itb = sequence.begin();
	std::vector<VeryLong> ::iterator ite = sequence.end();
	return std::count_if(itb, ite, IsEven);
}

int NumberSequenceGenerator::countOddNumbers()
{
	std::vector<VeryLong> ::iterator itb = sequence.begin();
	std::vector<VeryLong> ::iterator ite = sequence.end();
	return std::count_if(itb, ite, IsOdd);
}

void NumberSequenceGenerator::display()
{
	std::cout << "\nSequence: \n";
	for (auto it : sequence) {
		it.putvl();
	}
}
