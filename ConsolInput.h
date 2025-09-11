#pragma once
#include <string>

using namespace std;

class ConsolInput
{
public:
	int toInt(const string& inputObject);
	double toDouble(const string& inputObject);

	bool isInt(const string& inputObject);
	bool isDouble(const string& inputObject);

	void inputFullObject();

	int inputObjectId();
	string inputObjectName();
	int inputObjectQuantity();
	double inputObjectPrice();
	string inputObjectDate();
	string inputObjectRegisteredBy();
};

