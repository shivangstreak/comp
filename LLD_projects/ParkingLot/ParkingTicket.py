class ParkingTicket:
    def __init__(self, ticket_no, timestamp, exit, amount, status, vehicle, payment, entrance, exit_ins):
        self.__ticket_no = ticket_no
        self.__timestamp = timestamp
        self.__exit = exit
        self.__amount = amount
        self.__status = status

        # Following are the instances of their respective classes
        self__vehicle = vehicle
        self__payment = payment
        self__entrance = entrance
        self__exit_ins = exit_ins