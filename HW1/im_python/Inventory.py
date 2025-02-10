from Product import Product

class Inventory:
    def __init__(self):
        self.products = []
        
    def add_product(self, product):
        self.products.append(product)
        # print(f"Added {product.name} to inventory")
        
    def search_product(self, name):
        results = [product for product in self.products if name.lower() in product.name.lower()]
        if results:
            print("Search Results:")
            print("Name - Price - Stock - Qualities")
            for product in results:
                print(product.display_info())
                print("-" * 40)
            return results[0]
        else:
            print("No products found.")
            return None
            
    def search_section(self, section):
        results = [product for product in self.products if product.section.lower() == section.lower()]
        if results:
            print(f"Products in {section}:")
            print("Name - Price - Stock - Qualities")
            for product in results:
                print(product.display_info())
                print("-" * 40)
            return results
        else:
            print(f"No product in {section}")
                
    def search_category(self, category):
        results = [product for product in self.products if product.category.lower() == category.lower()]
        if results:
            print(f"Products in {category}:")
            print("Name - Price - Stock - Qualities")
            for product in results:
                print(product.display_info())
                print("-" * 40)
        else:
            print(f"No products in {category}")       
    
    def update_stock(self, name, add_quantity):
        print(f"Stock Updated for {name}.")
        for product in self.products:
            if product.name.lower() == name.lower():
                product.update_stock(add_quantity)
                return
        print("Product not found in the inventory")