#include "UserInteraction.h"

void UserInteraction::showMessage(std::string message)
{
	std::cout << message << "\n";
}

int UserInteraction::getN()
{
	int n = 0;
	std::cout << "Enter N (amount of elements of the sequence): ";
	std::cin >> n;
	return n;
}

VeryLong UserInteraction::getFirstTerm()
{

	VeryLong v{};
	std::cout << "Enter First Term : ";
	v.input_vl();
	return v;
}

VeryLong UserInteraction::getSecondParameterR()
{

	VeryLong v{};
	std::cout << "Enter Common Ratio: ";
	v.input_vl();
	return v;
}

VeryLong UserInteraction::getSecondParameterD()
{
	VeryLong v{};
	std::cout << "Enter Common Difference: ";
	v.input_vl();
	return v;
}
