#pragma once
#ifndef STORAGE_MAKER_UI_H_
#define STORAGE_MAKER_UI_H_
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include "Product.h"
#include "User.h"

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

    // user table widths
    const int u_widthId = 6;
    const int u_widthLogin = 20;
    const int u_widthRole = 12;
    const int u_widthRegBy = 20;
    const int u_widthDate = 20;

public:
    void showError(const std::string& error);
    void showAppMenu();
    void showAdminMenu();
    void showSearcherMenu();
    void showMessage(const std::string& message);
    void printAppHead(const std::string& tittle);
    void printProductHead();
    void printProduct(const Product& item);
    std::string center(const std::string& tittle, int width);

    // product printing helpers (templates)
    template<typename T>
    void printProductByPointer(T* item)
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
    void printProductByAdress(T& item)
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
    void printProduct(const Container& items)
    {
        printProductHead();
        for (const auto& item : items)
        {
            if constexpr (std::is_pointer_v<std::decay_t<decltype(item)>>) printProductByPointer(item);
            else printProductByAdress(item);
        }
        std::cout << " ==================================================================================================== \n";
    }

    // ---- user table API ----
    void printUserHead();
    void printUserRow(const User& u);
    void printUsers(const std::vector<User>& users);

    // single-user printing (by pointer)
    template<typename T>
    void printUserPointerRow(T* u)
    {
        std::cout << " --------------------------------------------------------------------------------------------- \n";
        std::cout << " | "
            << std::setw(u_widthId) << std::left << u->getId() << " | "
            << std::setw(u_widthLogin) << std::left << u->getName() << " | "
            << std::setw(u_widthRole) << std::left << User::roleToString(u->getRole()) << " | "
            << std::setw(u_widthRegBy) << std::left << u->getRegisteredBy() << " | "
            << std::setw(u_widthDate) << std::left << u->getDate() << " |\n";
    }

    // helper to print small box when no users
    void printNoUsers();

};
#endif
