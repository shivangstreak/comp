from enum import Enum

class OrderStatus(Enum):
  OPEN = 1
  FILLED = 2
  PARTIALLY_FILLED = 3
  CANCELED = 4


class TimeEnforcementType(Enum):
  GOOD_TILL_CANCELED = 1
  FILL_OR_KILL = 2
  IMMEDIATE_OR_CANCEL = 3
  ON_THE_OPEN = 4
  ON_THE_CLOSE = 5


class AccountStatus(Enum):
  ACTIVE = 1
  CLOSED = 2
  CANCELED = 3
  BLACKLISTED = 4
  NONE = 5


class Address:
  def __init__(self, street, city, state, zip_code, country):
    self.__street_address = street
    self.__city = city
    self.__state = state
    self.__zip_code = zip_code
    self.__country = country



a = AccountStatus.ACTIVE

b = AccountStatus.ACTIVE

if a==b:
    print("hhj")