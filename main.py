class Car():
    def __init__(self, color:str, reg_number:int):
        self.color = color
        self.__number = reg_number
    
    def get_number(self):
        return self.__number

    def __str__(self):
        return f"A {self.color} car with a number of {self.__number}"

car = Car("red", 1234)
car.__number = 1235 # doesnt work
print(car.get_number())
print(car)