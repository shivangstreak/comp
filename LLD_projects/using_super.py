from abc import ABC, abstractmethod

class IVechile(ABC):
    def __init__(self):
        self.a = 1
    @abstractmethod
    def drive(self):
        pass

class Car(IVechile):
    def __init__(self):
        super(Car, self).__init__()
        self.b=2

    def drive(self):
        print("Car is driving")

class VechileFactory():
    @staticmethod
    def get_vechile(vechile_type):
        if vechile_type=="car":
            return Car()

if __name__ == "__main__":
    car = VechileFactory.get_vechile("car")
    car.drive()
    print(car.a)
    print(car.b)