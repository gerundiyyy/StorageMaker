#pragma once
#ifndef STORAGE_MAKER_INPUT_H_
#define STORAGE_MAKER_INPUT_H_
#include <string>
#include "Item.h"
#include "ConsolUI.h"
using namespace std;

class InputManager
{
public:
	InputManager(ConsolUI& ui)
		: ui(&ui) {}

	int inputItemId();
	string inputItemName();
	int inputItemQuantity();
	double inputItemPrice();
	string inputItemDate();
	string inputItemRegisteredBy();

	void intError();
	void doubleError();
	void voidError();
	void boolError();

	int toInt(const string& inputObject);
	double toDouble(const string& inputObject);

	bool isInt(const string& inputObject);
	bool isDouble(const string& inputObject);
	/*bool isBool(const string& inputObject);*/
	bool isContinue() const;
	/*bool inputBool();*/

	int waitForKey();
	int inputMenu();
	Item inputFullItem();
private:
	ConsolUI* ui;
};
#endif
