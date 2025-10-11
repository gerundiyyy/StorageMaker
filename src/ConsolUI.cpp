#include "ConsolUI.h"

#include <iostream>
#include <string>
#include "InputManager.h"
#include "DataBaseManager.h"

using namespace std;
void ConsolUI::showMenu()
{
    cout << " =========================================================== \n";
    cout << " |                      StorageMaker Menu                  | \n";
    cout << " =========================================================== \n";
    cout << " | 1 - Вывод всех данных                                   | \n";
    cout << " | 2 - Поиск                                               | \n";
    cout << " | 3 - Запись                                              | \n";
    cout << " | 0 - Выход из программы                                  | \n";
    cout << " =========================================================== \n";
}

void ConsolUI::searchItem()
{
    cout << " =========================================================== \n";
    cout << " |                   StorageMaker: Поиск                   | \n";
    cout << " =========================================================== \n";
    cout << " | 1 - По ID                                               | \n";
    cout << " | 2 - По имени                                            | \n";
    cout << " | 3 - По количеству                                       | \n";
    cout << " | 4 - По цене                                             | \n";
    cout << " | 5 - По дате                                             | \n";
    cout << " | 6 - По зарегистрировавшему пользователю                 | \n";
    cout << " | 0 - Вернуться в меню                                    | \n";
    cout << " =========================================================== \n";
}


void ConsolUI::showMessage(const string& message)
{
	cout << message << endl;
}