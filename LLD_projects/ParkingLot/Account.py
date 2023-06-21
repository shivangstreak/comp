from abc import ABC, abstractmethod


class Account(ABC):
    # Data members
    def __init__(self, user_name, password, person, status):
        self.__user_name = user_name
        self.__password = password
        self.__person = person  # Refers to an instance of the Person class
        self.__status = status  # Refers to the AccountStatus enum

    @abstractmethod
    def reset_password(self):
        pass


class Admin(Account):
    def __init__(self, user_name, password, person, status):
        super(Admin, self).__init__(user_name, password, person, status)

    # spot here refers to an instance of the ParkingSpot class
    def add_parking_spot(self, spot):
        pass

    # display_board here refers to an instance of the DisplayBoard class
    def add_display_board(self, display_board):
        pass

    # entrance here refers to an instance of the Entrance class
    def add_entrance(self, entrance):
        pass

    # exit here refers to an instance of the Exit class
    def add_exit(self, exit):
        pass

    def reset_password(self):
        # Will implement the functionality in this class
        pass


class ParkingAttendant(Account):
    def __init__(self, user_name, password, person, status):
        super(ParkingAttendant, self).__init__(user_name, password, person, status)

    def process_ticket(self, ticket_number):
        pass

    def reset_password(self):
        # Will implement the functionality in this class
        pass
