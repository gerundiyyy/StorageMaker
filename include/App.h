#pragma once
#ifndef STORAGE_MAKER_APP_H_
#define STORAGE_MAKER_APP_H_
#include <string>

#include "ConsolUI.h"
#include "InputManager.h"
#include "DataBaseManager.h"
#include "Item.h"
#include "Storage.h"

class App
{
private:
	DataBaseManager db;
	Storage storage;
	ConsolUI ui;
	InputManager in;
	ItemExtractor ex;

	std::string currentUser;
public:
	void callMenu();
	void record();
	void printAll();
	void run();
	void search();
};

#endif