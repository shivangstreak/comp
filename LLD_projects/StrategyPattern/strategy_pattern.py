class Strategy:
    def execute(self, data):
        pass


class ConcreteStrategyA(Strategy):
    def execute(self, data):
        print("Executing strategy A with data:", data)


class ConcreteStrategyB(Strategy):
    def execute(self, data):
        print("Executing strategy B with data:", data)


class Context:
    def __init__(self, strategy):
        self._strategy = strategy

    def set_strategy(self, strategy):
        self._strategy = strategy

    def execute_strategy(self, data):
        self._strategy.execute(data)


# Example usage
strategy_a = ConcreteStrategyA()
strategy_b = ConcreteStrategyB()

context = Context(strategy_a)
context.execute_strategy("Hello")

context.set_strategy(strategy_b)
context.execute_strategy("World")



