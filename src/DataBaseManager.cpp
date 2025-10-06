#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "DataBaseManager.h"
#include "ObjectBD.h"
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

void DataBaseManager::recordObjectBD(const ObjectBD& obj) 
{
	ofstream file("data/product_data.txt", ios::app);
	if (!file) throw runtime_error("Не удалось открыть файл");
	file << obj.toText();
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

ObjectBD DataBaseManager::parseObject(const vector<string>& lines)
{
	ObjectBD obj;
	for (const auto& line : lines)
	{
		if (line.find("id: ") == 0)
			obj.setId(toInt(line.substr(4)));
		else if (line.find("Имя: ") == 0)
			obj.setName(line.substr(5));
		else if (line.find("Количество: ") == 0)
			obj.setQuantity(toInt(line.substr(12)));
		else if (line.find("Цена: ") == 0)
			obj.setPrice(toDouble(line.substr(6)));
		else if (line.find("Дата регистрации: ") == 0)
			obj.setDate(line.substr(18));
		else if (line.find("Кто зарегистрировал: ") == 0)
			obj.setRegisteredBy(line.substr(21));
	}
	return obj;
}	

vector <ObjectBD> DataBaseManager::readObjectBD()
{
	ifstream file("data/product_data.txt");
	if (!file) cout << ("Не удалось открыть файл") << endl;
	else if (file) cout << ("Удалось открыть файл") << endl;
	vector <ObjectBD> result;
	vector <string> buffer;
	string line;

	while (getline(file, line))
	{
		if (line == "===")
		{
			ObjectBD obj = parseObject(buffer);
			result.push_back(obj);
			buffer.clear();

			cout << "Объект добавлен!" << endl;
			/*obj.print();*/
		}
		else buffer.push_back(line);
	}
	return result;
}
