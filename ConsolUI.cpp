#include <iostream>
#include <string>
#include <sstream>
#include <regex>

#include "ConsolUI.h"
#include "DataBaseManager.h"
#include "ObjectBD.h"

using namespace std;

int ConsolUI::inputObjectId()
{
	string inputObject;
	int objectId;

	cout << "id: ";

	while (true) 
	{
		getline(cin, inputObject);

		stringstream isString(inputObject);
		double isDouble;

		if (isString >> isDouble && isString.eof())
		{
			if (isDouble == static_cast<int>(isDouble))
			{
				objectId = static_cast<int>(isDouble);
				break;
			}
			else cout << "Ошибка! Пожалуйста, введите целое число: ";
		}
		else cout << "Ошибка! Пожалуйста, введите число: ";
	}

	return objectId;
}

string ConsolUI::inputObjectName()
{
	string objectName;
	cout << "Имя: "; cin >> objectName;
	return objectName;

	cin.clear(); 
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int ConsolUI::inputObjectQuantity()
{
	string inputObject;
	int objectQuantity;

	cout << "Количество: ";

	while (true)
	{
		getline(cin, inputObject);

		stringstream isString(inputObject);
		double isDouble;

		if (isString >> isDouble && isString.eof())
		{
			if (isDouble == static_cast<int>(isDouble))
			{
				objectQuantity = static_cast<int>(isDouble);
				break;
			}
			else cout << "Ошибка! Пожалуйста, введите целое число: ";
		}
		else cout << "Ошибка! Пожалуйста, введите число: ";
	}

	return objectQuantity;
}

double ConsolUI::inputObjectPrice()
{
	string inputObject;
	double objectPrice;

	cout << "Цена: ";

	while (true)
	{
		getline(cin, inputObject);

		stringstream isString(inputObject);

		if (isString >> objectPrice && isString.eof()) break;
		else cout << "Ошибка! Пожалуйста, введите число: ";
	}

	return objectPrice;
}

string ConsolUI::inputObjectDate()
{
	string objectDate;
	cout << "Дата регистрации: "; cin >> objectDate;
	return objectDate;

	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string ConsolUI::inputObjectRegisteredBy()
{
	string objectRegisteredBy;
	cout << "Кто зарегестрировал: "; cin >> objectRegisteredBy;
	return objectRegisteredBy;

	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void ConsolUI::inputFullObject()
{
	DataBaseManager* DataBaseManager1 = new DataBaseManager("Name", 1);
	ObjectBD* inputObjectBD= new ObjectBD();

	inputObjectBD->setId(inputObjectId());
	inputObjectBD->setName(inputObjectName());
	inputObjectBD->setQuantity(inputObjectQuantity());
	inputObjectBD->setPrice(inputObjectPrice());
	inputObjectBD->setDate(inputObjectDate());
	inputObjectBD->setRegisteredBy(inputObjectRegisteredBy());
	cout << endl;

	DataBaseManager1->recordObjectBD(*inputObjectBD);

	delete inputObjectBD;
	delete DataBaseManager1;
}

void ConsolUI::showMenu() {
	cout << "Введём объект для записи"<< endl;
	inputFullObject();
}