#pragma once
#ifndef STORAGE_MAKER_UI_H_
#define STORAGE_MAKER_UI_H_
#include <string>
using namespace std;

class ConsolUI
{
public:
	void showMenu();
	void searchItem();
	void showMessage(const string& message);
};

#endif