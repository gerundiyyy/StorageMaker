#include "App.h"

int main()
{
	DataBaseManager* db = new DataBaseManager();
	ConsolUI* ui = new ConsolUI();
	InputManager* in = new InputManager(*ui);
	ItemExtractor* ex = new ItemExtractor();
	Storage* storage = new Storage(*ex, *in, *ui);
	App* app = new App(*db, *storage, *ui, *in);
	app->run();
	app->appMenu();
	delete db;
	delete storage;
	delete ui;
	delete in;
	delete ex;
	delete app;
}