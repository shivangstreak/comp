import threading
class Account:
    def __init__(self):
        self.balance = 100
        self.version = 0

    def withdraw(self, amount, expected_version):
        if self.version == expected_version:
            if self.balance >= amount:
                self.balance -= amount
                self.version += 1
                return True
            return False
        else:
            raise Exception("Data has changed")

account = Account()

def withdraw_thread():
    for _ in range(100):
        while True:
            try:
                version = account.version
                account.withdraw(1, version)
                break
            except Exception as e:
                continue

threads = [threading.Thread(target=withdraw_thread) for _ in range(10)]

for thread in threads:
    thread.start()

for thread in threads:
    thread.join()

print(account.balance)
