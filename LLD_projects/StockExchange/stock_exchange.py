# The StockExchange is a singleton class that ensures it will have only one active instance at a time
class __StockExchange(object):
    __instances = None

    def __new__(cls):
        if cls.__instances is None:
            cls.__instances = super(__StockExchange, cls).__new__(cls)
        return cls.__instances


class StockExchange(metaclass=__StockExchange):
    def __init__(self, ):

    def place_order(Order order

    ):
    pass