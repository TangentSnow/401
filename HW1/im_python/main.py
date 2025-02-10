from Product import Product
from Inventory import Inventory
from Menus import Menus

def main():
    inventory = Inventory()
    menus = Menus(inventory)
        
    inventory.add_product(Product(section="Indoor Sports", category="Vollyball", name="Pro Vollyball", price=50, quantity=10, qualities={"Material": "Leather", "Size": "Standard"}))
    inventory.add_product(Product(section="Outdoor Sports", category="Camping", name="Adventure Tent", price=150, quantity=5, qualities={"Size": "4-person", "Durability": "High", "Weather Rating": "Rainproof"}))
    inventory.add_product(Product(section="Outdoor Sports", category="Soccer", name="Large Goal Net", price=200, quantity=3, qualities={"Type": "Professional"}))

    while True:
        print("---------------- Welcome to Shopping and Inventory Management System ----------------")
        print("\n---- Main Menu ----")
        print("1. Customer Menu\n2. Manager Menu\n3. Exit")
        choice = input("Select an option: ")
            
        if choice == "1":
            menus.customer_menu()
        elif choice == "2":
            menus.manager_menu()
        elif choice == "3":
            print("Good-Bye...")
            break
        else:
            print("Inavlid Choice")
            
if __name__ == "__main__":
    main()