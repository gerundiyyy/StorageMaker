#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <stdlib.h>
#include "DataBaseManager.h"
#include "ObjectBD.h"
#include "InputManager.h"

using namespace std;

//Errors
void InputManager::intError()
{
	cout << "Ошибка! Пожалуйста, введите целое число: ";
}
void InputManager::doubleError()
{
	cout << "Ошибка! Пожалуйста, введите число: ";
}
void InputManager::voidError()
{
	cout << "Ошибка! Пожалуйста, введите значение: ";
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

int InputManager::inputObjectId()
{
	string objectId;
	while (true)
	{
		getline(cin, objectId);
		if (isInt(objectId) && !(objectId.empty())) break;
	}
	return toInt(objectId);
}

string InputManager::inputObjectName()
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

int InputManager::inputObjectQuantity()
{
	string objectQuantity;
	while (true)
	{
		getline(cin, objectQuantity);
		if (isInt(objectQuantity) && !(objectQuantity.empty())) break;
	}
	return toInt(objectQuantity);
}

double InputManager::inputObjectPrice()
{
	string objectPrice;
	while (true)
	{
		getline(cin, objectPrice);
		if (isDouble(objectPrice)) break;
	}
	return toDouble(objectPrice);
}

string InputManager::inputObjectDate()
{
	string objectDate;
	getline(cin, objectDate);
	return objectDate;
}

string InputManager::inputObjectRegisteredBy()
{
	string objectRegisteredBy;
	getline(cin, objectRegisteredBy);
	return objectRegisteredBy;
}

ObjectBD InputManager::inputFullObject()
{
	ObjectBD inputObjectBD;

	cout << "id: ";
	inputObjectBD.setId(inputObjectId());
	cout << "Имя: ";
	inputObjectBD.setName(inputObjectName());
	cout << "Количество: ";
	inputObjectBD.setQuantity(inputObjectQuantity());
	cout << "Цена: ";
	inputObjectBD.setPrice(inputObjectPrice());
	cout << "Дата регистрации: ";
	inputObjectBD.setDate(inputObjectDate());
	cout << "Кто зарегестрировал: ";
	inputObjectBD.setRegisteredBy(inputObjectRegisteredBy());
	cout << endl;

	return inputObjectBD;
}

int InputManager::inputMenu()
{
	string menuChoice;
	getline(cin, menuChoice);
	if (isInt(menuChoice)) return toInt(menuChoice);
	else intError();
}