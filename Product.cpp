#include "Product.h"
#include "Entity.h"

#include <iostream>
#include <string>
#include "DataBaseManager.h"
using namespace std;

//Constructor and Destructors
Product::Product(int id)
	: Entity(id), quantity(0), price(0),
	date("01-01-2000"), registeredBy("None") {}
Product::Product()
	: Entity() ,quantity(0), price(0),
	date("01-01-2000"), registeredBy("None") {}

//Setters
void Product::setQuantity(int quantity)
{
	this->quantity = quantity;
}
void Product::setPrice(double price)
{
	this->price = price;
}
void Product::setDate(const string& date)
{
	this->date = date;
}
void Product::setRegisteredBy(const string& registeredBy)
{
	this->registeredBy = registeredBy;
}

//Getters
int Product::getQuantity() const
{
	return quantity;
}
double Product::getPrice() const
{
	return price;
}
string Product::getDate() const
{
	return date;
}
string Product::getRegisteredBy() const
{
	return registeredBy;
}

string Product::toText() const
{
	return "Имя: " + getName() + "\n" +
		"id: " + std::to_string(getId()) + "\n" +
		"Количество: " + std::to_string(quantity) + "\n" +
		"Цена: " + std::to_string(price) + "\n" +
		"Дата регистрации: " + date + "\n" +
		"Кто зарегистрировал: " + registeredBy + "\n" +
		"===\n";
}

