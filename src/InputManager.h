#pragma once
#include <string>
#include "ObjectBD.h"

using namespace std;

class InputManager
{
private:
	/*int inputObjectId();*/
	string inputObjectName();
	int inputObjectQuantity();
	double inputObjectPrice();
	string inputObjectDate();
	string inputObjectRegisteredBy();
public:
	void intError();
	void doubleError();
	void voidError();

	int toInt(const string& inputObject);
	double toDouble(const string& inputObject);

	bool isInt(const string& inputObject);
	bool isDouble(const string& inputObject);

	int inputMenu();
	ObjectBD inputFullObject(int id);
};

