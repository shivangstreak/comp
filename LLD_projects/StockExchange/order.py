class OrderPart:
    def __init__(self, price, quantity, executed_at):
        self.__price = price
        self.__quantity = quantity
        self.__executed_at = executed_at


from abc import ABC, abstractmethod


class Order(ABC):
    def __init__(self, order_number, is_buy_order, status, time_enforcement, creation_time):
        self.__order_number = order_number
        self.__is_buy_order = is_buy_order
        self.__status = status
        self.__time_enforcement = time_enforcement
        self.__creation_time = creation_time
        self.__parts = {}

    def set_status(OrderStatus status

    ):
    pass


def save_in_database():
    pass


def add_order_parts(OrderParts parts

):
pass


class LimitOrder(Account):
    def __init__(self, order_number, is_buy_order, status, time_enforcement, creation_time):
        super().__init__(order_number, is_buy_order, status, time_enforcement, creation_time)


class StopLimitOrder(Account):
    def __init__(self, order_number, is_buy_order, status, time_enforcement, creation_time):
        super().__init__(order_number, is_buy_order, status, time_enforcement, creation_time)


class StopLossOrder(Account):
    def __init__(self, order_number, is_buy_order, status, time_enforcement, creation_time):
        super().__init__(order_number, is_buy_order, status, time_enforcement, creation_time)


class MarketOrder(Account):
    def __init__(self, order_number, is_buy_order, status, time_enforcement, creation_time):
        super().__init__(order_number, is_buy_order, status, time_enforcement, creation_time)