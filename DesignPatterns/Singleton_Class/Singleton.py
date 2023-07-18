class Singleton:
    __instance = None

    def __new__(cls, *args, **kwargs):
        if not cls.__instance:
            cls.__instance = super().__new__(cls)
        return cls.__instance

    def __init__(self, id, name, address, parking_rate):
        if not hasattr(self, 'initialized'):
            self.__id = id
            self.__name = name

            # Create initial entrance and exit hashmaps respectively
            self.__entrance = {}
            self.__exit = {}
            # Create a hashmap that identifies all currently generated tickets using their ticket number
            self.__tickets = {}

            self.initialized = True

class k:
    __instance = None

    def __new__(cls, *args, **kwargs):
        if not cls.__instance:
            cls.__instance = super().__new__(cls)
        return cls.__instance

    def __init__(self, a, b):
        self.a = a
        self.b = b

    def __repr__(self):
        return f"{self.a} : {self.b}"

p = k(1,2)
l = k(4,5)

print(l)
if p==l:
    print("aaa")


