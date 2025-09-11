#include <iostream>
#include <string>
#include <fstream>
#include "DataBaseManager.h"
#include "ObjectBD.h"
using namespace std;

//Construtors and Destructors
DataBaseManager::DataBaseManager(int id)
{
	this->id = id;
	cout << "DataBaseManager has been created!" << endl;
}

DataBaseManager::~DataBaseManager()
{
	cout << "DataBaseManager has been deleted!" << endl;
}

//Getters
int DataBaseManager::getId() const
{
	return id;
}

//Special 
void DataBaseManager::recordObjectBD(const ObjectBD& ObjectBD)
{
	/*ObjectsBD.push_back(ObjectBD);*/
	ofstream file_cout;
	file_cout.open("product_data.txt", ios::app);

	file_cout << "id: " << ObjectBD.getId() << endl;
	file_cout << "Имя: " << ObjectBD.getName() << endl;
	file_cout << "Количество: " << ObjectBD.getQuantity() << endl;
	file_cout << "Цена: " << ObjectBD.getPrice() << endl;
	file_cout << "Дата регистрации: " << ObjectBD.getDate() << endl;
	file_cout << "Кто зарегестрировал: " << ObjectBD.getRegisteredBy() << endl;
	file_cout << endl;

	file_cout.close();
}