#include <iostream>
#include <string>
#include "DataBaseManager.h"
#include "ObjectBD.h"
int main()
{
	ObjectBD* ObjectBD1 = new ObjectBD(5,"Name", 5, 8.5, "12-01-2007", "Gendos");
	DataBaseManager* DataBaseManager1 = new DataBaseManager("Name", 1);
	DataBaseManager1->recordObjectBD(*ObjectBD1);

	delete ObjectBD1;
	delete DataBaseManager1;
}