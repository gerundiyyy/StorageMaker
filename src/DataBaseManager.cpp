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

void DataBaseManager::setLastId(int lastId) 
{
	this->lastId= lastId;
}

//Special 

int DataBaseManager::toInt(const string& inputObject)
{
	stringstream isString(inputObject);
	int intObject;
	isString >> intObject;
	return intObject;
}
void DataBaseManager::recordObjectBD(const ObjectBD& obj, int lastId) 
{
	ofstream file("product_data.txt", ios::app);
	if (!file) throw runtime_error("Не удалось открыть файл");
	file << obj.toText();
	file.close();
	setLastId(lastId);
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
ifstream DataBaseManager::openFile(const std::string& fileName)
{
	ifstream file(fileName);
	if (!file.is_open()) {
		throw runtime_error("Не удалось открыть файл");
	}
	return file;
}
vector <ObjectBD> DataBaseManager::parseFile(ifstream& file)
{
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
		}
		else buffer.push_back(line);
	}
	return result;
}

vector <ObjectBD> DataBaseManager::readObjectBD()
{
	try 
	{
		ifstream file = openFile("data/product_data.txt");
		vector <ObjectBD> result = parseFile(file);
		file.close();
		return result;
	}
	catch (const exception& e) 
	{
		cout << e.what() << endl;
		return {};
	}
}
