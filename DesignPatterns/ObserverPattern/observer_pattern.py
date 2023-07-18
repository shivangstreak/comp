class Subject:
    def __init__(self):
        self._observers = []

    def attach(self, observer):
        self._observers.append(observer)

    def detach(self, observer):
        self._observers.remove(observer)

    def notify(self, message):
        for observer in self._observers:
            observer.update(message)


class Observer:
    def update(self, message):
        pass


# Example usage
class ConcreteObserver(Observer):
    def update(self, message):
        print("Received message:", message)


subject = Subject()
observer1 = ConcreteObserver()
observer2 = ConcreteObserver()

subject.attach(observer1)
subject.attach(observer2)

subject.notify("Hello observers!")

subject.detach(observer2)

subject.notify("Observer2 detached.")

