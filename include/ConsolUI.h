#pragma once
#ifndef STORAGE_MAKER_UI_H_
#define STORAGE_MAKER_UI_H_
#include <string>
using namespace std;

class ConsolUI
{
public:
	void showError(const string& error);
	void showAppMenu();
	void showSearcherMenu();
	void showMessage(const string& message);
};

#endif