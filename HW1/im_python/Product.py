class Product:
    def __init__(self, section, category, name, price, quantity, qualities=None):
        self.section = section
        self.category = category
        self.name = name
        self.price = price
        self.quantity = quantity
        self.qualities = qualities if qualities else {}
        
    def update_stock(self, add_quantity):
        self.quantity += add_quantity
        print(f"{self.name} stock updated to {self.quantity}")
        
    def display_info(self):
        qualities_str = ", ".join([f"{value}" for key, value in self.qualities.items()])
        return (
            f"{self.name} - ${self.price:.2f} - {self.quantity} - {qualities_str}"
        )
        
    def purchase(self, quantity, discount=0):
        if quantity <= 0:
            print(f"Please enter valid number of items")
            return None
        
        if quantity > self.quantity:
            print(f"Insufficient Stock. Only {self.quantity} avaliable")
            return None
        
        # Discount based on quantity
        if quantity >= 5:
            discount = 0.10  #10% off per item if 5 or more items are purchased
        elif quantity >= 10:
            discount = 0.20  #20% off per item if 10 or more items are purchased
        
        discounted_price = self.price * (1 - discount)
        total_cost = discounted_price * quantity
        undiscounted_cost = self.price * quantity
        
        self.update_stock(-quantity)
        print(f"Purchased {quantity} x {self.name} - Total Price: ${total_cost:.2f}")
        print(f"Total Savings: ${undiscounted_cost - total_cost}")