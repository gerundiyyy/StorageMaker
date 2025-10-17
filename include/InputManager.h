#pragma once
#ifndef STORAGE_MAKER_INPUT_H_
#define STORAGE_MAKER_INPUT_H_
#include <string>
#include "Product.h"
#include "ConsolUI.h"
using namespace std;

class InputManager
{
public:
	InputManager(ConsolUI& ui)
		: ui(&ui) {}

	int inputProductId();
	string inputProductName();
	int inputProductQuantity();
	double inputProductPrice();
	string inputProductDate();
	string inputProductRegisteredBy();

	void intError();
	void doubleError();
	void voidError();
	void boolError();

	int toInt(const string& inputObject);
	double toDouble(const string& inputObject);

	bool isInt(const string& inputObject);
	bool isDouble(const string& inputObject);
	bool isContinue() const;

	int waitForKey();
	int inputMenu();
	Product inputFullProduct();
private:
	ConsolUI* ui;
};
#endif
