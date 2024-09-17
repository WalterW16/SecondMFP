#pragma once
#include"string"
#include<iostream>
#include"VeryLong.h"
class UserInteraction
{
public:
	 void showMessage(std::string  message);	
	 int getN();
	 VeryLong getFirstTerm();
	 VeryLong getSecondParameterR();
	 VeryLong getSecondParameterD();
};

