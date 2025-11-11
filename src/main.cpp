#include "App.h"
#include <iostream>

int main()
{
    try {
        App app;
        app.run();
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка! : " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Неизвестная ошибка!\n";
        return 2;
    }
}
