#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <stdlib.h>
#include "DataBaseManager.h"
#include "ObjectBD.h"
#include "ConsolInput.h"

using namespace std;

//Checks and converters
int ConsolInput::toInt(const string& inputObject)
{
	stringstream isString(inputObject);
	int intObject;
	isString >> intObject;
	return intObject;
}

double ConsolInput::toDouble(const string& inputObject)
{
	stringstream isString(inputObject);
	double doubleObject;
	isString >> doubleObject;
	return doubleObject;
}

bool ConsolInput::isInt(const string& inputObject)
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
			cout << "������! ����������, ������� ����� �����: ";
			return false;
		}
	}
	else
	{
		cout << "������! ����������, ������� �����: ";
		return false;
	}
}

bool ConsolInput::isDouble(const string& inputObject)
{
	stringstream isString(inputObject);
	double isDouble;
	if (isString >> isDouble && isString.eof())
	{
		return true;
	}
	else
	{
		cout << "������! ����������, ������� �����: ";
		return false;
	}
}

//Inputs

int ConsolInput::inputObjectId()
{
	string objectId;
	while (true)
	{
		getline(cin, objectId);
		if (isInt(objectId) && !(objectId.empty())) break;
	}
	return toInt(objectId);
}

string ConsolInput::inputObjectName()
{
	string objectName;
	while (true)
	{
		getline(cin, objectName);
		if (!(objectName.empty())) break;
		else cout << "������! ����������, ������� ���: ";
	}

	return objectName;
}

int ConsolInput::inputObjectQuantity()
{
	string objectQuantity;
	while (true)
	{
		getline(cin, objectQuantity);
		if (isInt(objectQuantity) && !(objectQuantity.empty())) break;
	}
	return toInt(objectQuantity);
}

double ConsolInput::inputObjectPrice()
{
	string objectPrice;
	while (true)
	{
		getline(cin, objectPrice);
		if (isDouble(objectPrice)) break;
	}
	return toDouble(objectPrice);
}

string ConsolInput::inputObjectDate()
{
	string objectDate;
	getline(cin, objectDate);
	return objectDate;
}

string ConsolInput::inputObjectRegisteredBy()
{
	string objectRegisteredBy;
	getline(cin, objectRegisteredBy);
	return objectRegisteredBy;
}

void ConsolInput::inputFullObject()
{
	DataBaseManager* DataBaseManager1 = new DataBaseManager(1);
	ObjectBD* inputObjectBD = new ObjectBD();

	cout << "id: ";
	inputObjectBD->setId(inputObjectId());
	cout << "���: ";
	inputObjectBD->setName(inputObjectName());
	cout << "����������: ";
	inputObjectBD->setQuantity(inputObjectQuantity());
	cout << "����: ";
	inputObjectBD->setPrice(inputObjectPrice());
	cout << "���� �����������: ";
	inputObjectBD->setDate(inputObjectDate());
	cout << "��� ���������������: ";
	inputObjectBD->setRegisteredBy(inputObjectRegisteredBy());
	cout << endl;

	DataBaseManager1->recordObjectBD(*inputObjectBD);

	delete inputObjectBD;
	delete DataBaseManager1;
}