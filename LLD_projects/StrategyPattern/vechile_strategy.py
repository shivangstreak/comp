from abc import ABC, abstractmethod

# Here we have defined IDriveStrategy strategy , two types sports and off road
# You can use these strategy to change the behaviour of a Car object's drive

class IDriveStrategy(ABC):
    @abstractmethod
    def drive(self):
        pass


class sportsDriveStrategy(IDriveStrategy):
    def drive(self):
        print("This is SPORTS MODE")


class offroadDriveStrategy(IDriveStrategy):
    def drive(self):
        print("This is OFF ROAD MODE")


class IVehicle(ABC):
    # Here stating that drive_strategy is of type IDriveStrategy
    def __init__(self, drive_strategy: IDriveStrategy):
        self.drive_strategy = drive_strategy

    @abstractmethod
    def drive(self):
        pass


class Car(IVehicle):
    def __init__(self, car_number, drive_strategy):
        super(Car, self).__init__(drive_strategy)
        self.car_number = car_number

    def drive(self):
        print(self.car_number)
        self.drive_strategy.drive()

car1 = Car(1, sportsDriveStrategy())
car2 = Car(2, offroadDriveStrategy())

car1.drive()
car2.drive()

change_car_1_mode = True
if change_car_1_mode:
    # Using Strategy pattern you can change the behaviour of objects on the fly easily
    car1.drive_strategy = offroadDriveStrategy()

car1.drive()
