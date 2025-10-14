#include "DataBaseManager.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Item.h"

using namespace std;

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
	if (!file) throw runtime_error("Не удалось открыть файл");
	file << item.toText();
	file.close();
}
void DataBaseManager::recordItem(const std::vector<Item>& items) const
{
	try {
		ofstream file("data/product_data.txt", ofstream::out | ofstream::trunc);
		if (!file) throw runtime_error("Не удалось открыть файл");
		for (const auto& item : items)
		{
			file << item.toText();
		}
		file.close();
	}
	catch (const runtime_error& e)
	{
		cerr << "Ошибка записи";
	}
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

void DataBaseManager::parseLine(Item& item, const string& line)
{
	if (line.find("id: ") == 0)
		item.setId(toInt(line.substr(4)));
	else if (line.find("Имя: ") == 0)
		item.setName(line.substr(5));
	else if (line.find("Количество: ") == 0)
		item.setQuantity(toInt(line.substr(12)));
	else if (line.find("Цена: ") == 0)
		item.setPrice(toDouble(line.substr(6)));
	else if (line.find("Дата регистрации: ") == 0)
		item.setDate(line.substr(18));
	else if (line.find("Кто зарегистрировал: ") == 0)
		item.setRegisteredBy(line.substr(21));
}

Item DataBaseManager::parseItem(const vector<string>& lines)
{
	Item item;
	try {
		for (const auto& line : lines) parseLine(item, line);
	}
	catch (const exception& e)
	{
		throw runtime_error(string{ "Ошибка парсинга Item: " } + e.what());
	}
	return item;
}	

vector <Item> DataBaseManager::readItem()
{
	ifstream file("data/product_data.txt");
	if (!file) throw runtime_error("Не удалось открыть файл");
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
		}
		else buffer.push_back(line);
	}
	return result;
}
void DataBaseManager::createFile(const string& adress)
{
	ofstream ensure(adress, ios::app);
}
