from abc import ABCMeta, abstractmethod
# This is the base class for the bot
# This is just an abstraction and many types of bot can inherit this

class BotBase(metaclass=ABCMeta):
    def __init__(self, ware_house):
        # warehouse object is here
        self.ware_house = ware_house
        self.capacity = self.ware_house.bot_cap

    @abstractmethod
    def calculate_result(self):
        pass