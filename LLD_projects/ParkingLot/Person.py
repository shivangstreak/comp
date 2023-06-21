from enum import Enum


# Enumeration
class PaymentStatus(Enum):
    COMPLETED = 1
    FAILED = 2
    PENDING = 3
    UNPAID = 4
    REFUNDED = 5


class AccountStatus(Enum):
    ACTIVE = 1
    CLOSED = 2
    CANCELED = 3
    BLACKLISTED = 4
    NONE = 5


# Custom Person data type class
class Person:
    def __init__(self, name, address, phone, email):
        self.__name = name
        self.__address = address
        self.__phone = phone
        self.__email = email


# Custom Address data type class
class Address:
    def __init__(self, zip_code, address, city, state, country):
        self.__zip_code = zip_code
        self.__address = address
        self.__city = city
        self.__state = state
        self.__country = country


print("yo")
print(PaymentStatus.UNPAID)
