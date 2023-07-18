class Subject:
    def __init__(self):
        self._observers = []

    def attach(self, observer):
        self._observers.append(observer)

    def detach(self, observer):
        self._observers.remove(observer)

    def notify(self, data):
        for observer in self._observers:
            observer.update(data)


class Observer:
    def update(self, data):
        pass


# Example usage
class TemperatureSensor(Subject):
    def __init__(self):
        super().__init__()
        self._temperature = None

    @property
    def temperature(self):
        return self._temperature

    @temperature.setter
    def temperature(self, value):
        self._temperature = value
        self.notify(value)


class Display(Observer):
    def update(self, data):
        print("Temperature changed:", data)


sensor = TemperatureSensor()
display1 = Display()
display2 = Display()

sensor.attach(display1)
sensor.attach(display2)

sensor.temperature = 25.5

sensor.detach(display2)

sensor.temperature = 30.0
