#include <iostream>
#include <string>
#include "DataBaseManager.h"
#include "ObjectBD.h"
using namespace std;

//Constructor and Destructors
ObjectBD::ObjectBD(int id)
	: id(id), name("None"), quantity(0), price(0),
	date("01-01-2000"), registeredBy("None") {}
ObjectBD::ObjectBD()
	: id(0), name("None"), quantity(0), price(0),
	date("01-01-2000"), registeredBy("None") {}

//Setters
void ObjectBD::setId(int id)
{
	this->id = id;
}
void ObjectBD::setName(const string& name)
{
	this->name = name;
}
void ObjectBD::setQuantity(int quantity)
{
	this->quantity = quantity;
}
void ObjectBD::setPrice(double price)
{
	this->price = price;
}
void ObjectBD::setDate(const string& date)
{
	this->date = date;
}
void ObjectBD::setRegisteredBy(const string& registeredBy)
{
	this->registeredBy = registeredBy;
}

//Getters
int ObjectBD::getId() const
{
	return id;
}
string ObjectBD::getName() const
{
	return name;
}
int ObjectBD::getQuantity() const
{
	return quantity;
}
double ObjectBD::getPrice() const
{
	return price;
}
string ObjectBD::getDate() const
{
	return date;
}
string ObjectBD::getRegisteredBy() const
{
	return registeredBy;
}

string ObjectBD::toText() const 
{
	return "id: " + to_string(id) + "\n" +
		"Имя: " + name + "\n" +
		"Количество: " + to_string(quantity) + "\n" +
		"Цена: " + to_string(price) + "\n" +
		"Дата регистрации: " + date + "\n" +
		"Кто зарегистрировал: " + registeredBy + "\n"
		"===\n";
}

void ObjectBD::print() const
{
	cout << "id: " << id << "\n"
		<< "Имя: " << name << "\n"
		<< "Количество: " << quantity << "\n"
		<< "Цена: " << price << "\n"
		<< "Дата регистрации: " << date << "\n"
		<< "Кто зарегистрировал: " << registeredBy << "\n"
		<< "===\n";
}
