#pragma once
#ifndef STORAGE_MAKER_UI_H_
#define STORAGE_MAKER_UI_H_
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include "Item.h"
using namespace std;

class ConsolUI
{
private:
    const int widthhead = 96;
    const int widthId = 6;
    const int widthName = 20;
    const int widthQty = 10;
    const int widthPrice = 10;
    const int widthDate = 15;
    const int widthUser = 20;
public:
	void showError(const std::string& error);
	void showAppMenu();
	
	void showSearcherMenu();
	void showMessage(const std::string& message);
    void printAppHead(const std::string& tittle);
    void printItemHead();
	void printItem(const Item& item);
    std::string center(const std::string& tittle, int width);

    template<typename T>
    void printItemByPointer(T* item)
    {
        std::cout << " ---------------------------------------------------------------------------------------------------- \n";
        std::cout << " | "
            << std::setw(widthId) << std::left << item->getId() << " | "
            << std::setw(widthName) << std::left << item->getName() << " | "
            << std::setw(widthQty) << std::left << item->getQuantity() << " | "
            << std::setw(widthPrice) << std::left << std::fixed << std::setprecision(2) << item->getPrice() << " | "
            << std::setw(widthDate) << std::left << item->getDate() << " | "
            << std::setw(widthUser) << std::left << item->getRegisteredBy() << " |\n";
    }
    template<typename T>
    void printItemByAdress(T& item)
    {
        std::cout << " ---------------------------------------------------------------------------------------------------- \n";
        std::cout << " | "
            << std::setw(widthId) << std::left << item.getId() << " | "
            << std::setw(widthName) << std::left << item.getName() << " | "
            << std::setw(widthQty) << std::left << item.getQuantity() << " | "
            << std::setw(widthPrice) << std::left << std::fixed << std::setprecision(2) << item.getPrice() << " | "
            << std::setw(widthDate) << std::left << item.getDate() << " | "
            << std::setw(widthUser) << std::left << item.getRegisteredBy() << " |\n";
    }

    template<typename Container>
    void printItem(const Container& items)
    {
        printItemHead();
        for (const auto& item : items)
        {
            if constexpr (std::is_pointer_v<std::decay_t<decltype(item)>>) printItemByPointer(item);
            else printItemByAdress(item);
        }
        std::cout << " ==================================================================================================== \n";
    }
};

#endif