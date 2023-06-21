from abc import ABC, abstractmethod

class Search(ABC):
  def search_symbol(self, symbol):
    None

class StockInventory(Search):
  def __init__(self, inventory_name, last_update):
    self.__inventory_name = inventory_name
    self.__last_update = last_update

  def search_symbol(self, symbol):
    pass