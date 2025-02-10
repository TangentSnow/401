from Inventory import Inventory
from Product import Product

class Menus:
    def __init__(self, inventory):
        self.inventory = inventory
        
    def customer_menu(self):
        while True:
            print("\n----------- Customer Menu -------------")
            print("1. View All Products\n2. Browse by Section\n3. Browse by Category\n4. Search for Product\n5. Purchase\n6. Exit")
            choice = input("Select an option: ")
            
            if choice == "1":
                print("\n---- All Products ----")
                for product in self.inventory.products:
                    print(product.display_info())
                    print("-" * 60)
            elif choice == "2":
                section = input("Enter section name (e.g., Outdoor Sports): ")
                self.inventory.search_section(section)
            elif choice == "3":
                category = input("Enter category name (e.g., Vollyball): ")
                self.inventory.search_category(category)
            elif choice == "4":
                name = input("Enter product name: ")
                self.inventory.search_product(name)
            elif choice == "5":
                name = input("Enter product you want to buy: ")
                product = self.inventory.search_product(name)
                if product:
                    quantity = int(input("How many: "))
                    product.purchase(quantity)
                else:
                    print(f"{name} not found.")
            elif choice =="6":
                print("Good-Bye...")
                break
            else:
                print("Invalid Choice")
                
    def manager_menu(self):
        while True:
            print("\n----------- Manager Menu -------------")
            print("1. View Full Inventory\n2. View Inventory by Section\n3. View Inventory by Category\n4. Add Product\n5. Update Stock\n 6. Exit")
            choice = input("Select an option: ")
            
            if choice == "1":
                print("\n---- Current Inventory ----")
                for product in self.inventory.products:
                    print(product.display_info())
                    print("-" * 60)
            elif choice == "2":
                section = input("\nEnter section name (e.g., Outdoor Sports): ")
                self.inventory.search_section(section)
            elif choice == "3":
                category = input("\nEnter category name (e.g., Vollyball): ")
                self.inventory.search_category(category)
            elif choice == "4":
                print("\n---- Add new product ----")
                section = input("Enter section name (e.g., Outdoor Sports): ")
                category = input("Enter category name (e.g., Vollyball): ")
                name = input("Enter product name: ")
                price = float(input("Enter price: "))
                quantity = int(input("Enter quantity: "))
                qualities = {}
                while True:
                    quality_key = input("Enter quality category (e.g., size) or type 'done' to finish: ")
                    if quality_key.lower() == "done":
                        break
                    quality_value = input(f"Enter value for '{quality_key}': ")
                    qualities[quality_key] = quality_value
                self.inventory.add_product(Product(section, category, name, price, quantity, qualities))
                print(f"{name} has be successfully added!")
            elif choice == "5":
                name = input("Enter product name to update stock: ")
                add_quantity = int (input("Enter the change in quantity (+/-): "))
                self.inventory.update_stock(name, add_quantity)
            elif choice == "6":
                print("Good-Bye...")
                break
            else:
                print("Invalid Choice")