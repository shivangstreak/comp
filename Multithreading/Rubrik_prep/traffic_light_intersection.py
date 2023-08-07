from threading import Lock
# Simply make sure operation in each thread is atomic and won't be bothered by other threads. Lock() can also be replaced by Semaphore(1). 
# https://leetcode.com/problems/traffic-light-controlled-intersection/description/

from threading import Lock
# Simply make sure operation in each thread is atomic and won't be bothered by other threads. Lock() can also be replaced by Semaphore(1).
#
class TrafficLight:
    def __init__(self):
        self.lock = Lock()
        self.green = 1

    def carArrived(
        self,
        carId: int,                      # ID of the car
        roadId: int,                     # ID of the road the car travels on. Can be 1 (road A) or 2 (road B)
        direction: int,                  # Direction of the car
        turnGreen: 'Callable[[], None]', # Use turnGreen() to turn light to green on current road
        crossCar: 'Callable[[], None]'   # Use crossCar() to make car cross the intersection
    ) -> None:

        with self.lock:
            if self.green != roadId:
                self.green = roadId
                turnGreen()
            crossCar()

class TrafficLight:
    def __init__(self):
        self.green = 1

    def carArrived(
        self,
        carId: int,                      # ID of the car
        roadId: int,                     # ID of the road the car travels on. Can be 1 (road A) or 2 (road B)
        direction: int,                  # Direction of the car
        turnGreen: 'Callable[[], None]', # Use turnGreen() to turn light to green on current road
        crossCar: 'Callable[[], None]'   # Use crossCar() to make car cross the intersection
    ) -> None:
        if roadId != self.green:
            turnGreen()
            self.green = roadId
        crossCar()

import threading

class TrafficLight:
    def __init__(self):
        self.lock = threading.Lock()
        self.greenOnA = True

    def carArrived(
        self,
        carId: int,                      # ID of the car
        roadId: int,                     # ID of the road the car travels on. Can be 1 (road A) or 2 (road B)
        direction: int,                  # Direction of the car
        turnGreen: 'Callable[[], None]', # Use turnGreen() to turn light to green on current road
        crossCar: 'Callable[[], None]'   # Use crossCar() to make car cross the intersection
    ) -> None:
        with self.lock:
            if (roadId == 1 and not self.greenOnA or roadId == 2 and self.greenOnA):
                turnGreen()
                self.greenOnA = not self.greenOnA
            crossCar()
