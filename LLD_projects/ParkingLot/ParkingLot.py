# The __ParkingLot is a singleton class that ensures it will have only one active instance at a time
# Both the Entrance and Exit classes use this class to create and close parking tickets

class ParkingLot:
    __instance = None

    def __new__(cls, *args, **kwargs):
        if not cls.__instance:
            cls.__instance = super().__new__(cls)
        return cls.__instance

    def __init__(self, id, name, address, parking_rate):
        if not hasattr(self, 'initialized'):
            self.__id = id
            self.__name = name
            self.__address = address
            self.__parking_rate = parking_rate

            # Create initial entrance and exit hashmaps respectively
            self.__entrance = {}
            self.__exit = {}
            # Create a hashmap that identifies all currently generated tickets using their ticket number
            self.__tickets = {}

            self.initialized = True

    # entrance here refers to an instance of the Entrance class
    def add_entrance(self, entrance):
        # Implement the logic to add an entrance
        pass

    # exit here refers to an instance of the Exit class
    def add_exit(self, exit):
        # Implement the logic to add an exit
        pass

    # This function allows parking tickets to be available at multiple entrances
    # vehicle here refers to an Vehicle of the Exit class
    # Returns a ParkingTicket instance
    def get_parking_ticket(self, vehicle):
        # Implement the logic to get a parking ticket
        pass

    # type here refers to an instance of the ParkingSpot class
    def is_full(self, spot_type):
        # Implement the logic to check if the parking lot is full for the given spot type
        pass
