#include <iostream>
#include <string>
#include <fstream>
#include "DataBaseManager.h"
using namespace std;

//Construtors and Destructors
DataBaseManager::DataBaseManager(const string& name, int id)
{
	this->id = id;
	cout << "DataBaseManager has been created!";
}

DataBaseManager::~DataBaseManager()
{
	cout << "DataBaseManager has been deleted!";
}

//Getters
int DataBaseManager::getId()
{
	return this->id;
}

//Product DataBaseManager::getProduct(int i)
//{
//	return product[i];
//}

//Special 
void DataBaseManager::recordProduct(const string& text)
{
	ofstream file_cout;
	file_cout.open("product_data.txt", ios::app);
	file_cout << text;
	file_cout.close();
}