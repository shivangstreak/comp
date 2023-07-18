import threading

class SingletonMeta(type):
    _instances = {}
    _lock: threading.Lock = threading.Lock()

    def __call__(cls, *args, **kwargs):
        with cls._lock:
            if cls not in cls._instances:
                instance = super().__call__(*args, **kwargs)
                cls._instances[cls] = instance
        return cls._instances[cls]


class Singleton(metaclass=SingletonMeta):
    def __init__(self, name):
        self.business_name = name

    def some_business_logic(self):
        """
        Finally, any singleton should define some business logic,
        which can be executed on its instance.
        """
        print(f"some_business_logic regarding {self.business_name}")
        # ...


if __name__ == "__main__":
    # The client code.

    s1 = Singleton("TATA")
    s2 = Singleton("APPLE")

    if id(s1) == id(s2):
        print("Singleton works, both variables contain the same instance.")
    else:
        print("Singleton failed, variables contain different instances.")

    s1.some_business_logic()