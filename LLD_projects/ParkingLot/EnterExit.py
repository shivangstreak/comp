class Entrance:
    def __init__(self, id, ticket):
        self.__id = id
        self.__ticket = ticket  # Refers to an instance of the ParkingTicket class

    # ticket here refers to an instance of the ParkingTicket class
    def get_ticket(self, ticket):
        pass


class Exit:
    def __init__(self, id, ticket):
        self.__id = id
        self.__ticket = ticket  # Refers to an instance of the ParkingTicket class

    # ticket here refers to an instance of the ParkingTicket class
    def validate_ticket(self, ticket):
        pass
