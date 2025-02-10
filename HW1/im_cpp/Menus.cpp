#include "Menus.h"
#include <iostream>
#include <map>

Menus::Menus(Inventory& inventory) : inventory(inventory) {}

void Menus::customer_menu() {
    while (true) {
        cout << "\n----------- Customer Menu -------------" << endl;
        cout << "1. View All Products\n2. Browse by Section\n3. Browse by Category\n4. Search for Product\n5. Purchase\n6. Exit" << endl;
        cout << "Select an option: ";
        string choice;
        getline(cin, choice);

        if (choice == "1") {
            cout << "\n---- All Products ----" << endl;
            for (const auto& product : inventory.get_products()) {
                cout << product.display_info() << endl;
                cout << string(60, '-') << endl;
            }
        } else if (choice == "2") {
            cout << "Enter section name (e.g., Outdoor Sports): ";
            string section;
            getline(cin, section);
            inventory.search_section(section);
        } else if (choice == "3") {
            cout << "Enter category name (e.g., Volleyball): ";
            string category;
            getline(cin, category);
            inventory.search_category(category);
        } else if (choice == "4") {
            cout << "Enter product name: ";
            string name;
            getline(cin, name);
            inventory.search_product(name);
        } else if (choice == "5") {
            cout << "Enter product you want to buy: ";
            string name;
            getline(cin, name);
            Product* product = inventory.search_product(name);
            if (product) {
                cout << "How many: ";
                int quantity;
                cin >> quantity;
                cin.ignore();  // Clear the newline character from the input buffer
                product->purchase(quantity);
            } else {
                cout << name << " not found." << endl;
            }
        } else if (choice == "6") {
            cout << "Good-Bye..." << endl;
            break;
        } else {
            cout << "Invalid Choice" << endl;
        }
    }
}

// Manager menu
void Menus::manager_menu() {
    while (true) {
        cout << "\n----------- Manager Menu -------------" << endl;
        cout << "1. View Full Inventory\n2. View Inventory by Section\n3. View Inventory by Category\n4. Add Product\n5. Update Stock\n6. Exit" << endl;
        cout << "Select an option: ";
        string choice;
        getline(cin, choice);

        if (choice == "1") {
            cout << "\n---- Current Inventory ----" << endl;
            for (const auto& product : inventory.get_products()) {
                cout << product.display_info() << endl;
                cout << string(60, '-') << endl;
            }
        } else if (choice == "2") {
            cout << "\nEnter section name (e.g., Outdoor Sports): ";
            string section;
            getline(cin, section);
            inventory.search_section(section);
        } else if (choice == "3") {
            cout << "\nEnter category name (e.g., Volleyball): ";
            string category;
            getline(cin, category);
            inventory.search_category(category);
        } else if (choice == "4") {
            cout << "\n---- Add new product ----" << endl;
            cout << "Enter section name (e.g., Outdoor Sports): ";
            string section;
            getline(cin, section);
            cout << "Enter category name (e.g., Volleyball): ";
            string category;
            getline(cin, category);
            cout << "Enter product name: ";
            string name;
            getline(cin, name);
            cout << "Enter price: ";
            double price;
            cin >> price;
            cin.ignore();  // Clear the newline character from the input buffer
            cout << "Enter quantity: ";
            int quantity;
            cin >> quantity;
            cin.ignore();  // Clear the newline character from the input buffer

            map<string, string> qualities;
            while (true) {
                cout << "Enter quality category (e.g., size) or type 'done' to finish: ";
                string quality_key;
                getline(cin, quality_key);
                if (quality_key == "done") {
                    break;
                }
                cout << "Enter value for '" << quality_key << "': ";
                string quality_value;
                getline(cin, quality_value);
                qualities[quality_key] = quality_value;
            }

            inventory.add_product(Product(section, category, name, price, quantity, qualities));
            cout << name << " has been successfully added!" << endl;
        } else if (choice == "5") {
            cout << "Enter product name to update stock: ";
            string name;
            getline(cin, name);
            cout << "Enter the change in quantity (+/-): ";
            int add_quantity;
            cin >> add_quantity;
            cin.ignore();  // Clear the newline character from the input buffer
            inventory.update_stock(name, add_quantity);
        } else if (choice == "6") {
            cout << "Good-Bye..." << endl;
            break;
        } else {
            cout << "Invalid Choice" << endl;
        }
    }
}