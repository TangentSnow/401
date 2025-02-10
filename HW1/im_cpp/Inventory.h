#ifndef Inventory_h
#define Inventory_h
#include "Product.h"
#include <vector>
#include <string>
using namespace std;

class Inventory {
private:
    vector<Product> products;

public:
    Inventory();

    const vector<Product>& get_products(){ return products; }
    void add_product(const Product& product);
    Product* search_product(const string& name);
    void search_section(const string& section);
    void search_category(const string& category);
    void update_stock(const string& name, int add_quantity);
};

#endif