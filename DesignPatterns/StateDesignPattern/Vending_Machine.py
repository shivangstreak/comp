from abc import ABC, abstractmethod
class VendingMachine:
    def __init__(self):
        self.state = IdleState(self)

    def change_state(self, state):
        self.state = state

    def insert_coin(self):
        self.state.insert_coin()

    def select_product(self):
        self.state.select_product()

    def dispense_product(self):
        self.state.dispense_product()

    def refill(self):
        self.state.refill()


class VendingMachineState:
    def __init__(self, machine):
        self.machine = machine

    def insert_coin(self):
        raise NotImplementedError()

    def select_product(self):
        raise NotImplementedError()

    def dispense_product(self):
        raise NotImplementedError()

    def refill(self):
        raise NotImplementedError()


class IdleState(VendingMachineState):
    def insert_coin(self):
        print("Coin inserted.")
        self.machine.change_state(HasCoinState(self.machine))

    def select_product(self):
        print("Please insert a coin first.")

    def dispense_product(self):
        print("Please insert a coin first.")

    def refill(self):
        print("Refilling vending machine.")


class HasCoinState(VendingMachineState):
    def insert_coin(self):
        print("Coin already inserted.")

    def select_product(self):
        print("Product selected.")
        self.machine.change_state(SoldState(self.machine))

    def dispense_product(self):
        print("Please select a product first.")

    def refill(self):
        print("Please wait for the current transaction to complete.")


class SoldState(VendingMachineState):
    def insert_coin(self):
        print("Please wait, product dispensing.")

    def select_product(self):
        print("Please wait, product dispensing.")

    def dispense_product(self):
        print("Product dispensed.")
        self.machine.change_state(IdleState(self.machine))

    def refill(self):
        print("Please wait for the current transaction to complete.")


# Example usage
machine = VendingMachine()

machine.select_product()  # Please insert a coin first.

machine.insert_coin()  # Coin inserted.
machine.select_product()  # Product selected.
machine.dispense_product()  # Product dispensed.

machine.refill()  # Refilling vending machine.
machine.insert_coin()  # Coin inserted.
