class Singleton(type):
    _instances = {}

    def __call__(cls, *args, **kwargs):
        if cls not in cls._instances:
            cls._instances[cls] = super(Singleton, cls).__call__(*args, **kwargs)
        return cls._instances[cls]


# This using wrapper design pattern too here
class Logger(metaclass=Singleton):
    def __init__(self, wrapped_object=None):
        if wrapped_object:
            self._wrapped = wrapped_object

    def perform_action(self):
        print("Logging: Before action")
        self._wrapped.perform_action()
        print("Logging: After action")


class ObjectToWrap:
    def perform_action(self):
        print("Object action")


# Usage
wrapped_object = ObjectToWrap()
logger1 = Logger(wrapped_object)
logger1.perform_action()

# Even if we try to create a new Logger, it returns the existing instance
logger2 = Logger(ObjectToWrap())
logger2.perform_action()  # The action of the initially created logger is performed

print(logger1 == logger2)  # Returns: True
