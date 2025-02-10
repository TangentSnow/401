#ifndef Menus_h
#define Menus_h

#include "Inventory.h"
#include <string>

using namespace std;

class Menus {
private:
    Inventory& inventory;

public:
    Menus(Inventory& inventory);
    
    void customer_menu();
    void manager_menu();
};

#endif