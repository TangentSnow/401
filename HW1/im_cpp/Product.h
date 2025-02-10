#ifndef Product_h
#define Product_h
#include <iostream>
#include <string>
#include <map>
using namespace std;

class Product {
private:
    string section;
    string category;
    string name;
    double price;
    int quantity;
    map<string, string> qualities;

public:
    Product(string section, string category, string name, double price, int quantity, map<string, string> qualities);

    string get_name(){return name;}
    string get_category(){return category;}
    string get_section(){return section;}
    
    void update_stock(int add_quantity);
    string display_info() const;
    void purchase(int quantity, double discount = 0.0);
};

#endif