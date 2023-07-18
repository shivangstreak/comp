class Payment:
    def __init__(self):
        self.paymentId = 0
        # Other payment details



# # Payment is an abstract class
# from abc import ABC, abstractmethod
#
# class Payment(ABC):
#   # Data members
#   def __init__(self, amount, timestamp, status):
#     self.__amount = amount
#     self.__timestamp = timestamp
#     self.__status = status # Refers to the PaymentStatus enum
#
#   @abstractmethod
#   def make_payment(self):
#     pass
#
# class Cash(Payment):
#   def __init__(self, amount, timestamp, status):
#     super().__init__(amount, timestamp, status)
#
#   def make_payment(self):
#     # functionality
#     pass
#
# class CreditCard(Payment):
#   # Data members
#   def __init__(self, amount, timestamp, status, name_on_card, card_number, billing_address, code):
#     self.__name_on_card = name_on_card
#     self.__card_number = card_number
#     self.__billing_address = billing_address
#     self.__code = code
#     super().__init__(amount, timestamp, status)
#
#   def make_payment(self):
#     # functionality
#     pass