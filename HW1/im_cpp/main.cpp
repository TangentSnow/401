#include "Menus.h"
#include <iostream>
#include <map>

using namespace std;

int main() {
    Inventory inventory;

    map<string, string> qualities1 = {{"Material", "Leather"}, {"Size", "Standard"}};
    inventory.add_product(Product("Indoor Sports", "Volleyball", "Pro Volleyball", 50, 10, qualities1));

    map<string, string> qualities2 = {{"Size", "4-person"}, {"Durability", "High"}, {"Weather Rating", "Rainproof"}};
    inventory.add_product(Product("Outdoor Sports", "Camping", "Adventure Tent", 150, 5, qualities2));

    map<string, string> qualities3 = {{"Type", "Professional"}};
    inventory.add_product(Product("Outdoor Sports", "Soccer", "Large Goal Net", 200, 3, qualities3));

    Menus menus(inventory);

    while (true) {
        cout << "\n---------------- Welcome to Shopping and Inventory Management System ----------------" << endl;
        cout << "\n---- Main Menu ----" << endl;
        cout << "1. Customer Menu\n2. Manager Menu\n3. Exit" << endl;
        cout << "Select an option: ";
        string choice;
        getline(cin, choice);

        if (choice == "1") {
            menus.customer_menu();
        } else if (choice == "2") {
            menus.manager_menu();
        } else if (choice == "3") {
            cout << "Good-Bye..." << endl;
            break;
        } else {
            cout << "Invalid Choice" << endl;
        }
    }

    return 0;
}