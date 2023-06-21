class StockPosition:
  def __init__(self, symbol, quantity):
    self.__symbol = symbol
    self.__quantity = quantity

class StockLot:
  def __init__(self, iot_number, buying_order):
    self.__iot_number = iot_number
    self.__buying_order = buying_order

  def get_buying_price():
    pass