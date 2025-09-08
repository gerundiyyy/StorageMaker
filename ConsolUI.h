#pragma once
#include <string>

using namespace std;

class ConsolUI
{
public:
	void showMenu();
	void inputFullObject();

	int inputObjectId();
	string inputObjectName();
	int inputObjectQuantity();
	double inputObjectPrice();
	string inputObjectDate();
	string inputObjectRegisteredBy();
};

