#include <iostream>
#include <string>
#include <windows.h>;
#include <stdlib.h>
#include "ConsolUI.h"
#include "DataBaseManager.h"
#include "ObjectBD.h"

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	setlocale(LC_ALL, "Russian");

	ConsolUI UI;
	UI.showMenu();
}