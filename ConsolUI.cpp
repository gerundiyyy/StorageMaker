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
			else cout << "������! ����������, ������� ����� �����: ";
		}
		else cout << "������! ����������, ������� �����: ";
	}

	return objectId;
}

string ConsolUI::inputObjectName()
{
	string objectName;
	cout << "���: "; cin >> objectName;
	return objectName;

	cin.clear(); 
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int ConsolUI::inputObjectQuantity()
{
	string inputObject;
	int objectQuantity;

	cout << "����������: ";

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
			else cout << "������! ����������, ������� ����� �����: ";
		}
		else cout << "������! ����������, ������� �����: ";
	}

	return objectQuantity;
}

double ConsolUI::inputObjectPrice()
{
	string inputObject;
	double objectPrice;

	cout << "����: ";

	while (true)
	{
		getline(cin, inputObject);

		stringstream isString(inputObject);

		if (isString >> objectPrice && isString.eof()) break;
		else cout << "������! ����������, ������� �����: ";
	}

	return objectPrice;
}

string ConsolUI::inputObjectDate()
{
	string objectDate;
	cout << "���� �����������: "; cin >> objectDate;
	return objectDate;

	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string ConsolUI::inputObjectRegisteredBy()
{
	string objectRegisteredBy;
	cout << "��� ���������������: "; cin >> objectRegisteredBy;
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
	cout << "����� ������ ��� ������"<< endl;
	inputFullObject();
}