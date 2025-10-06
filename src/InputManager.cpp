#include "InputManager.h"

#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include "DataBaseManager.h"
#include "Item.h"
using namespace std;

//Errors
void InputManager::intError()
{
	cout << "������! ����������, ������� ����� �����: ";
}
void InputManager::doubleError()
{
	cout << "������! ����������, ������� �����: ";
}
void InputManager::voidError()
{
	cout << "������! ����������, ������� ��������: ";
}

//Checks and converters
int InputManager::toInt(const string& inputObject)
{
	stringstream isString(inputObject);
	int intObject;
	isString >> intObject;
	return intObject;
}

double InputManager::toDouble(const string& inputObject)
{
	stringstream isString(inputObject);
	double doubleObject;
	isString >> doubleObject;
	return doubleObject;
}

bool InputManager::isInt(const string& inputObject)
{
	stringstream isString(inputObject);
	double isDouble;
	if (isString >> isDouble && isString.eof())
	{
		if (isDouble == static_cast<int>(isDouble))
		{
			return true;
		}
		else
		{
			intError();
			return false;
		}
	}
	else
	{
		doubleError();
		return false;
	}
}

bool InputManager::isDouble(const string& inputObject)
{
	stringstream isString(inputObject);
	double isDouble;
	if (isString >> isDouble && isString.eof())
	{
		return true;
	}
	else
	{
		doubleError();
		return false;
	}
}

//Inputs

int InputManager::inputItemId()
{
	string objectId;
	while (true)
	{
		getline(cin, objectId);
		if (isInt(objectId) && !(objectId.empty())) break;
	}
	return toInt(objectId);
}

string InputManager::inputItemName()
{
	string objectName;
	while (true)
	{
		getline(cin, objectName);
		if (!(objectName.empty())) break;
		else voidError();
	}

	return objectName;
}

int InputManager::inputItemQuantity()
{
	string objectQuantity;
	while (true)
	{
		getline(cin, objectQuantity);
		if (isInt(objectQuantity) && !(objectQuantity.empty())) break;
	}
	return toInt(objectQuantity);
}

double InputManager::inputItemPrice()
{
	string objectPrice;
	while (true)
	{
		getline(cin, objectPrice);
		if (isDouble(objectPrice)) break;
	}
	return toDouble(objectPrice);
}

string InputManager::inputItemDate()
{
	string objectDate;
	getline(cin, objectDate);
	return objectDate;
}

string InputManager::inputItemRegisteredBy()
{
	string objectRegisteredBy;
	getline(cin, objectRegisteredBy);
	return objectRegisteredBy;
}

Item InputManager::inputFullItem()
{
	Item inputItem;

	cout << "id: ";
	inputItem.setId(inputItemId());
	cout << "���: ";
	inputItem.setName(inputItemName());
	cout << "����������: ";
	inputItem.setQuantity(inputItemQuantity());
	cout << "����: ";
	inputItem.setPrice(inputItemPrice());
	cout << "���� �����������: ";
	inputItem.setDate(inputItemDate());
	cout << "��� ���������������: ";
	inputItem.setRegisteredBy(inputItemRegisteredBy());
	cout << endl;

	return inputItem;
}

int InputManager::inputMenu()
{
	string menuChoice;
	getline(cin, menuChoice);
	if (isInt(menuChoice)) return toInt(menuChoice);
	else intError();
}