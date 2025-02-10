#include "Inventory.h"
#include <algorithm>
#include <iostream>

Inventory::Inventory() {}

void Inventory::add_product(const Product& product) {
    products.push_back(product);
}

Product* Inventory::search_product(const string& name) {
    vector<Product*> results;

    // Case-insensitive search
    for (auto& product : products) {
        string product_name = product.get_name();
        string lower_name = name;
        transform(product_name.begin(), product_name.end(), product_name.begin(), ::tolower);
        transform(lower_name.begin(), lower_name.end(), lower_name.begin(), ::tolower);

        if (product_name.find(lower_name) != string::npos) {
            results.push_back(&product);
        }
    }

    if (!results.empty()) {
        cout << "Search Results:" << endl;
        cout << "Name - Price - Stock - Qualities" << endl;
        for (auto product : results) {
            cout << product->display_info() << endl;
            cout << string(40, '-') << endl;
        }
        return results[0];
    } else {
        cout << "No products found." << endl;
        return nullptr;
    }
}

void Inventory::search_section(const string& section) {
    vector<Product*> results;

    for (auto& product : products) {
        string product_section = product.get_section();
        string lower_section = section;
        transform(product_section.begin(), product_section.end(), product_section.begin(), ::tolower);
        transform(lower_section.begin(), lower_section.end(), lower_section.begin(), ::tolower);

        if (product_section == lower_section) {
            results.push_back(&product);
        }
    }

    if (!results.empty()) {
        cout << "Products in " << section << ":" << endl;
        cout << "Name - Price - Stock - Qualities" << endl;
        for (auto product : results) {
            cout << product->display_info() << endl;
            cout << string(40, '-') << endl;
        }
    } else {
        cout << "No products in " << section << endl;
    }
}

void Inventory::search_category(const string& category) {
    vector<Product*> results;

    for (auto& product : products) {
        string product_category = product.get_category();
        string lower_category = category;
        transform(product_category.begin(), product_category.end(), product_category.begin(), ::tolower);
        transform(lower_category.begin(), lower_category.end(), lower_category.begin(), ::tolower);

        if (product_category == lower_category) {
            results.push_back(&product);
        }
    }

    if (!results.empty()) {
        cout << "Products in " << category << ":" << endl;
        cout << "Name - Price - Stock - Qualities" << endl;
        for (auto product : results) {
            cout << product->display_info() << endl;
            cout << string(40, '-') << endl;
        }
    } else {
        cout << "No products in " << category << endl;
    }
}

void Inventory::update_stock(const string& name, int add_quantity) {
    bool found = false;

    for (auto& product : products) {
        string product_name = product.get_name();
        string lower_name = name;
        transform(product_name.begin(), product_name.end(), product_name.begin(), ::tolower);
        transform(lower_name.begin(), lower_name.end(), lower_name.begin(), ::tolower);

        if (product_name == lower_name) {
            product.update_stock(add_quantity);
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Product not found in the inventory" << endl;
    }
}