# ParkingSpot is an abstract class
from abc import ABC, abstractmethod


class ParkingSpot(ABC):
    def __init__(self, id, isFree, vehicle):
        self.__id = id
        self.__isFree = isFree
        self.__vehicle = vehicle  # Refers to an instance of the Vehicle class

    def get_is_free(self):
        pass

    # vehicle here refers to an instance of the Vehicle class
    @abstractmethod
    def assign_vehicle(self, vehicle):
        pass

    def remove_vehicle(self):
        pass


class Handicapped(ParkingSpot):
    # vehicle here refers to an instance of the Vehicle class
    def __init__(self, id, isFree, vehicle):
        super(Handicapped, self).__init__(id, isFree, vehicle)

    # vehicle here refers to an instance of the Vehicle class
    def assign_vehicle(self, vehicle):
        pass


class Compact(ParkingSpot):
    # vehicle here refers to an instance of the Vehicle class
    def __init__(self, id, isFree, vehicle):
        super(Compact, self).__init__(id, isFree, vehicle)

    # vehicle here refers to an instance of the Vehicle class
    def assign_vehicle(self, vehicle):
        pass


class Large(ParkingSpot):
    # vehicle here refers to an instance of the Vehicle class
    def __init__(self, id, isFree, vehicle):
        super(Large, self).__init__(id, isFree, vehicle)

    # vehicle here refers to an instance of the Vehicle class
    def assign_vehicle(self, vehicle):
        pass


class Motorcycle(ParkingSpot):
    # vehicle here refers to an instance of the Vehicle class
    def __init__(self, id, isFree, vehicle):
        super(Motorcycle, self).__init__(id, isFree, vehicle)

    # vehicle here refers to an instance of the Vehicle class
    def assign_vehicle(self, vehicle):
        pass
