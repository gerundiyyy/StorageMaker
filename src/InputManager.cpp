#include "InputManager.h"

#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include "ProductManager.h"
#include "Product.h"
using namespace std;

//Errors
void InputManager::boolError()
{
	ui->showMessage("Ошибка! Пожалуйста, введите 1 или 0: ");
}
void InputManager::intError()
{
	ui->showMessage("Ошибка! Пожалуйста, введите целое число : ");
}
void InputManager::doubleError()
{
	ui->showMessage("Ошибка! Пожалуйста, введите число: ");
}
void InputManager::voidError()
{
	ui->showMessage("Ошибка! Пожалуйста, введите значение: ");
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
		if (isDouble == static_cast<int>(isDouble)) return true;
		else intError(); return false;
	}
	else doubleError(); return false;
}

bool InputManager::isDouble(const string& inputObject)
{
	stringstream isString(inputObject);
	double isDouble;
	if (isString >> isDouble && isString.eof()) return true;
	else doubleError(); return false;
}

//Inputs

bool InputManager::isContinue() const
{
	ui->showMessage("Продолжить действие? (1 - да, 0 - нет)");
	bool isContinue;
	cin >> isContinue;
	std::cin.clear();
	std::cin.ignore(32767, '\n');
	return isContinue;
}

int InputManager::inputProductId()
{
	string objectId;
	while (true)
	{
		getline(cin, objectId);
		if (isInt(objectId) && !(objectId.empty())) break;
	}
	return toInt(objectId);
}

string InputManager::inputProductName()
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

int InputManager::inputProductQuantity()
{
	string objectQuantity;
	while (true)
	{
		getline(cin, objectQuantity);
		if (isInt(objectQuantity) && !(objectQuantity.empty())) break;
	}
	return toInt(objectQuantity);
}

double InputManager::inputProductPrice()
{
	string objectPrice;
	while (true)
	{
		getline(cin, objectPrice);
		if (isDouble(objectPrice)) break;
	}
	return toDouble(objectPrice);
}

string InputManager::inputProductDate()
{
	string objectDate;
	getline(cin, objectDate);
	return objectDate;
}

string InputManager::inputProductRegisteredBy()
{
	string objectRegisteredBy;
	getline(cin, objectRegisteredBy);
	return objectRegisteredBy;
}

Product InputManager::inputFullProduct()
{
	Product inputItem;

	cout << "id: ";
	inputItem.setId(inputProductId());
	cout << "Имя: ";
	inputItem.setName(inputProductName());
	cout << "Количество: ";
	inputItem.setQuantity(inputProductQuantity());
	cout << "Цена: ";
	inputItem.setPrice(inputProductPrice());
	cout << "Дата регистрации: ";
	inputItem.setDate(inputProductDate());
	cout << "Кто зарегестрировал: ";
	inputItem.setRegisteredBy(inputProductRegisteredBy());

	return inputItem;
}
int InputManager::waitForKey()
{
	string s;
	getline(cin, s); // просто ждём Enter или любой ввод
	if (s.empty()) return 1;   // пустой ввод — считать "продолжить"
	if (isInt(s)) return toInt(s); // если ввели число — вернуть его (0 = назад)
	return 1;
}
int InputManager::inputMenu()
{
	string menuChoice;
	while (true)
	{
		getline(cin, menuChoice);
		if (isInt(menuChoice)) return toInt(menuChoice);
		intError();
		ui->showMessage("Повторите ввод: ");
	}
}