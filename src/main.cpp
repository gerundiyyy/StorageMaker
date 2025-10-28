#include "ProductManager.h"
#include "ProductStorage.h"
#include "UserManager.h"
#include "AuthManager.h"
#include "ConsolUI.h"
#include "InputManager.h"
#include "ItemExtractor.h"
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
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown fatal error\n";
        return 2;
    }
}
