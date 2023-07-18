import threading
# For these examples, let's imagine we're dealing with a simple banking system,
# and our Account class represents a bank account with a balance.


# In this example, we use Python's built-in threading module to create a lock.' \
#  Whenever a thread wants to withdraw money from the account,' \
#  it must first acquire the lock.' \
#  This prevents other threads from simultaneously modifying the account's balance.

class Account:
    def __init__(self):
        self.balance = 100
        self.lock = threading.Lock()

    def withdraw(self, amount):
        with self.lock:
            if self.balance >= amount:
                self.balance -= amount
                return True
            return False

account = Account()

def withdraw_thread():
    for _ in range(100):
        account.withdraw(1)

threads = [threading.Thread(target=withdraw_thread) for _ in range(10)]

for thread in threads:
    thread.start()

for thread in threads:
    thread.join()

print(account.balance)
