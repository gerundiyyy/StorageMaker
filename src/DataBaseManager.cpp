#include "DataBaseManager.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Item.h"

using namespace std;

int DataBaseManager::getLastId() const
{
	return lastId;
}

//Special 

int DataBaseManager::toInt(const string& inputObject)
{
	stringstream isString(inputObject);
	int intObject;
	isString >> intObject;
	return intObject;
}

void DataBaseManager::recordItem(const Item& item)
{
	ofstream file("data/product_data.txt", ios::app);
	if (!file) throw runtime_error("�� ������� ������� ����");
	file << item.toText();
	file.close();
}

double DataBaseManager::toDouble(const string& inputObject)
{
	string sanitized = inputObject;
	replace(sanitized.begin(), sanitized.end(), ',', '.');
	std::stringstream isString(sanitized);
	double doubleObject;
	isString >> doubleObject;
	return doubleObject;
}

Item DataBaseManager::parseItem(const vector<string>& lines)
{
	Item item;
	for (const auto& line : lines)
	{
		if (line.find("id: ") == 0)
			item.setId(toInt(line.substr(4)));
		else if (line.find("���: ") == 0)
			item.setName(line.substr(5));
		else if (line.find("����������: ") == 0)
			item.setQuantity(toInt(line.substr(12)));
		else if (line.find("����: ") == 0)
			item.setPrice(toDouble(line.substr(6)));
		else if (line.find("���� �����������: ") == 0)
			item.setDate(line.substr(18));
		else if (line.find("��� ���������������: ") == 0)
			item.setRegisteredBy(line.substr(21));
	}
	return item;
}	

vector <Item> DataBaseManager::readItem()
{
	ifstream file("data/product_data.txt");
	if (!file) cout << ("�� ������� ������� ����") << endl;
	else if (file) cout << ("������� ������� ����") << endl;
	vector <Item> result;
	vector <string> buffer;
	string line;

	while (getline(file, line))
	{
		if (line == "===")
		{
			Item obj = parseItem(buffer);
			result.push_back(obj);
			buffer.clear();

			cout << "������ ��������!" << endl;
		}
		else buffer.push_back(line);
	}
	return result;
}
