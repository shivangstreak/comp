from abc import ABC, abstractmethod


class TransferMoney(ABC):
    def __init__(self, id, creation_date, from_account, to_account):
        self.__id = id
        self.__creation_date = creation_date
        self.__from_account = from_account
        self.__to_account = to_account

    @abstractmethod
    def initiate_transaction():
        pass


class ElectronicBank(TransferMoney):
    def __init__(self, id, creation_date, from_account, to_account, bank_name):
        super().__init__(id, creation_date, from_account, to_account)
        self.__bank_name = bank_name

    def initiate_transaction():


# functionality

class Wire(TransferMoney):
    def __init__(self, id, creation_date, from_account, to_account, wire):
        super().__init__(id, creation_date, from_account, to_account)
        self.__wire = wire

    def initiate_transaction():


# functionality

class Check(TransferMoney):
    def __init__(self, id, creation_date, from_account, to_account, check_number):
        super().__init__(id, creation_date, from_account, to_account)
        self.__check_number = check_number

    def initiate_transaction():


# functionality

class DepositMonet:
    def __init__(self, transaction_id):
        self.__transaction_id = transaction_id


class WithdrawMoney:
    def __init__(self, transaction_id):
        self.__transaction_id = transaction_id