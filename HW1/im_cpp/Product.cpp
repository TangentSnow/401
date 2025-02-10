#include "Product.h"

Product::Product(string section, string category, string name, double price, int quantity, map<string, string> qualities)
    : section(section), category(category), name(name), price(price), quantity(quantity), qualities(qualities) {}

void Product::update_stock(int add_quantity) {
    quantity += add_quantity;
    cout << name << " stock updated to " << quantity << endl;
}

string Product::display_info() const{
    string qualities_str = "";
    for (const auto& pair : qualities) {
        qualities_str += pair.second + ", ";
    }
    if (!qualities_str.empty()) {
        qualities_str.pop_back();
        qualities_str.pop_back();
    }

    return name + " - $" + to_string(price) + " - " + to_string(quantity) + " - " + qualities_str;
}

void Product::purchase(int quantity_to_buy, double discount) {
    if (quantity_to_buy <= 0) {
        cout << "Please enter a valid number of items" << endl;
        return;
    }

    if (quantity_to_buy > quantity) {
        cout << "Insufficient Stock. Only " << quantity << " available" << endl;
        return;
    }

    if (quantity_to_buy >= 10) {
        discount = 0.20;
    } else if (quantity_to_buy >= 5) {
        discount = 0.10;
    }

    double discounted_price = price * (1 - discount);
    double total_cost = discounted_price * quantity_to_buy;
    double undiscounted_cost = price * quantity_to_buy;

    update_stock(-quantity_to_buy);

    cout << "Purchased " << quantity_to_buy << " x " << name << " - Total Price: $" << total_cost << endl;
    cout << "Total Savings: $" << (undiscounted_cost - total_cost) << endl;
}