#pragma once
#ifndef STORAGE_MAKER_INPUT_H_
#define STORAGE_MAKER_INPUT_H_

#include <string>
#include "Product.h"
#include "ConsolUI.h"

class InputManager
{
public:
    explicit InputManager(ConsolUI& ui)
        : ui(&ui) {}

    int inputProductId();
    std::string inputProductName();
    int inputProductQuantity();
    double inputProductPrice();
    std::string inputProductDate();
    std::string inputProductRegisteredBy();

    void intError() const;
    void doubleError() const;
    void voidError() const;
    void boolError() const;

    int toInt(const std::string& inputObject) const;
    double toDouble(const std::string& inputObject) const;

    bool isInt(const std::string& inputObject) const;
    bool isDouble(const std::string& inputObject) const;
    bool isContinue() const;

    int waitForKey();
    int inputMenu();
    Product inputFullProduct();

    // методы, которые использует App
    int inputNumberAllowZero();
    double inputDoubleAllowZero();
    std::string inputOptionalString();

private:
    ConsolUI* ui;

    // простой безопасный getline (не меняет поток состояния наружу)
    bool readLine(std::string& out) const;
    std::string trim(const std::string& s) const;
};

#endif // STORAGE_MAKER_INPUT_H_
