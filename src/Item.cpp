#include "Item.h"

#include <iostream>
#include <string>
#include "DataBaseManager.h"
using namespace std;

//Constructor and Destructors
Item::Item(int id)
	: id(id), name("None"), quantity(0), price(0),
	date("01-01-2000"), registeredBy("None") {}
Item::Item()
	: id(0), name("None"), quantity(0), price(0),
	date("01-01-2000"), registeredBy("None") {}

//Setters
void Item::setId(int id)
{
	this->id = id;
}
void Item::setName(const string& name)
{
	this->name = name;
}
void Item::setQuantity(int quantity)
{
	this->quantity = quantity;
}
void Item::setPrice(double price)
{
	this->price = price;
}
void Item::setDate(const string& date)
{
	this->date = date;
}
void Item::setRegisteredBy(const string& registeredBy)
{
	this->registeredBy = registeredBy;
}

//Getters
int Item::getId() const
{
	return id;
}
string Item::getName() const
{
	return name;
}
int Item::getQuantity() const
{
	return quantity;
}
double Item::getPrice() const
{
	return price;
}
string Item::getDate() const
{
	return date;
}
string Item::getRegisteredBy() const
{
	return registeredBy;
}

string Item::toText() const
{
	return "id: " + to_string(id) + "\n" +
		"Имя: " + name + "\n" +
		"Количество: " + to_string(quantity) + "\n" +
		"Цена: " + to_string(price) + "\n" +
		"Дата регистрации: " + date + "\n" +
		"Кто зарегистрировал: " + registeredBy + "\n"
		"===\n";
}

void Item::print() const
{
	cout << "id: " << id << "\n"
		<< "Имя: " << name << "\n"
		<< "Количество: " << quantity << "\n"
		<< "Цена: " << price << "\n"
		<< "Дата регистрации: " << date << "\n"
		<< "Кто зарегистрировал: " << registeredBy << "\n"
		<< "===\n";
}
