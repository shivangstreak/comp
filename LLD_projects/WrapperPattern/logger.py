class Logger:
    def __init__(self, wrapped_object):
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
logger = Logger(wrapped_object)

logger.perform_action()
