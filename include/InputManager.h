#pragma once
#ifndef STORAGE_MAKER_INPUT_H_
#define STORAGE_MAKER_INPUT_H_
#include <string>
#include "Item.h"

using namespace std;

class InputManager
{
private:
	int inputItemId();
	string inputItemName();
	int inputItemQuantity();
	double inputItemPrice();
	string inputItemDate();
	string inputItemRegisteredBy();
public:
	void intError();
	void doubleError();
	void voidError();

	int toInt(const string& inputObject);
	double toDouble(const string& inputObject);

	bool isInt(const string& inputObject);
	bool isDouble(const string& inputObject);

	int inputMenu();
	Item inputFullItem();
};
#endif
