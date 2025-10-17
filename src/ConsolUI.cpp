#include "ConsolUI.h"

#include <iostream>
#include <string>
#include <iomanip>
#include "InputManager.h"
#include "ProductManager.h"
#include "Product.h"

using namespace std;
void ConsolUI::showAppMenu()
{
    printAppHead("StorageMaker");
    cout << " | " << setw(widthhead) << left << "1 - Вывод всех данных" << " | \n";
    cout << " ---------------------------------------------------------------------------------------------------- \n";
    cout << " | " << setw(widthhead) << left << "2 - Поиск " << " | \n";
    cout << " ---------------------------------------------------------------------------------------------------- \n";
    cout << " | " << setw(widthhead) << left << "3 - Запись" << " | \n";
    cout << " ---------------------------------------------------------------------------------------------------- \n";
    cout << " | " << setw(widthhead) << left << "4 - Удалить товар" << " | \n";
    cout << " ---------------------------------------------------------------------------------------------------- \n";
    cout << " | " << setw(widthhead) << left << "5 - Изменить товар" << " | \n";
    cout << " ---------------------------------------------------------------------------------------------------- \n";
    cout << " | " << setw(widthhead) << left << "0 - Выход из программы" << " | \n";
    cout << " ==================================================================================================== \n";
}
void ConsolUI::showSearcherMenu()
{
    printAppHead("Поиск");
    cout << " | " << setw(widthhead) << left << "1 - По ID" << " | \n";
    cout << " ---------------------------------------------------------------------------------------------------- \n";
    cout << " | " << setw(widthhead) << left << "2 - По имени" << " | \n";
    cout << " ---------------------------------------------------------------------------------------------------- \n";
    cout << " | " << setw(widthhead) << left << "3 - По количеству" << " | \n";
    cout << " ---------------------------------------------------------------------------------------------------- \n";
    cout << " | " << setw(widthhead) << left << "4 - По цене" << " | \n";
    cout << " ---------------------------------------------------------------------------------------------------- \n";
    cout << " | " << setw(widthhead) << left << "5 - По дате" << " | \n";
    cout << " ---------------------------------------------------------------------------------------------------- \n";
    cout << " | " << setw(widthhead) << left << "6 - По зарегистрировавшему пользователю" << " | \n";
    cout << " ---------------------------------------------------------------------------------------------------- \n";
    cout << " | " << setw(widthhead) << left << "0 - Вернуться в меню" << " | \n";
    cout << " ==================================================================================================== \n";
}

void ConsolUI::printAppHead(const string& tittle)
{
    cout << " ==================================================================================================== \n";
    cout << " | "
        << setw(widthhead) << center(tittle, widthhead) << " |\n";
    cout << " ==================================================================================================== \n";
}
void ConsolUI::printProductHead()
{
    cout << " ==================================================================================================== \n";
    cout << " | "
        << setw(widthhead) << center("ТОВАРЫ", widthhead) << " |\n";
    cout << " ==================================================================================================== \n";
    cout << " | "
        << setw(widthId) << left << "Id" << " | "
        << setw(widthName) << left << "Имя" << " | "
        << setw(widthQty) << left << "Количество" << " | "
        << setw(widthPrice) << left << "Цена" << " | "
        << setw(widthDate) << left << "Дата" << " | "
        << setw(widthUser) << left << "Зарегистрировал" << " |\n";

}
string ConsolUI::center(const string& tittle, int width)
{
    string result;
    int spaces = (width - tittle.length()) / 2;
    for (int i = 0; i < spaces; i++)
    {
        result += " ";
    }
    result += tittle;
    for (int i = 0; i < spaces; i++)
    {
        result += " ";
    }
    return result;
}
void ConsolUI::printProduct(const Product& item)
{
    printProductHead();
    printProductByAdress(item);
}
void ConsolUI::showMessage(const string& message)
{
	cout << message << endl;
}
void ConsolUI::showError(const string& error)
{
    cout << "!!!" << error << "!!!" << endl;
}