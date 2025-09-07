#include <iostream>
#include <string>
#include "DataBaseManager.h"

int main()
{
	DataBaseManager* DataBaseManager1 = new DataBaseManager("Name", 1);
	DataBaseManager1->recordProduct("Lol");
}