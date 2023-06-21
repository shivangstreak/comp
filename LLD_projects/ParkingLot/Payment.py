# Payment is an abstract class
from abc import ABC, abstractmethod


class Payment(ABC):
    def __init__(self, amount, status, timestamp):
        self.__amount = amount
        self.__status = status  # Refers to the PaymentStatus enum
        self.__timestamp = timestamp

    @abstractmethod
    def initiate_transaction(self):
        pass


class Cash(Payment):
    def __init__(self, amount, status, timestamp):
        super(Cash, self).__init__(amount, status, timestamp)

    def initiate_transaction(self):
        pass


class CreditCard(Payment):
    def __init__(self, amount, status, timestamp):
        super(CreditCard, self).__init__(amount, status, timestamp)

    def initiate_transaction(self):
        pass
