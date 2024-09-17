#pragma once
#include"Functors.h"
#include<conio.h>

class NumberSequenceGenerator
{
private:
	std::vector<VeryLong> sequence;
public:
	NumberSequenceGenerator()=default;
	NumberSequenceGenerator(std::vector<VeryLong> NewSequence);
	NumberSequenceGenerator(const NumberSequenceGenerator& other);
	void GenerateArithmeticProgression(VeryLong firstTerm , VeryLong CommonDifference, int n);
	void GenerateGeometricProgression(VeryLong firstTerm, VeryLong commonRatio, int n);
	int countPrimaryNumbers();
	int countEvenNumbers();
	int countOddNumbers();
	void display();
};

