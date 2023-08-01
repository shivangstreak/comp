import threading
import time
from enum import Enum

class TimeUnit(Enum):
    NANOSECONDS = 1e-9
    MICROSECONDS = 1e-6
    MILLISECONDS = 1e-3
    SECONDS = 1
    MINUTES = 60
    HOURS = 3600
    DAYS = 86400

    def to_seconds(self, duration):
        return duration * self.value

class ScheduledExecutorService:
    def schedule(self, command, delay, unit):
        delay_in_seconds = unit.to_seconds(delay)
        timer = threading.Timer(delay_in_seconds, command)
        timer.start()
        return timer

    def scheduleAtFixedRate(self, command, initialDelay, period, unit):
        initial_delay_in_seconds = unit.to_seconds(initialDelay)
        period_in_seconds = unit.to_seconds(period)

        def run_periodically():
            next_run = time.time() + period_in_seconds
            while True:
                command()
                time_to_next_run = next_run - time.time()
                if time_to_next_run > 0:
                    time.sleep(time_to_next_run)
                next_run += period_in_seconds

        timer = threading.Timer(initial_delay_in_seconds, run_periodically)
        timer.start()
        return timer

    def scheduleWithFixedDelay(self, command, initialDelay, delay, unit):
        initial_delay_in_seconds = unit.to_seconds(initialDelay)
        delay_in_seconds = unit.to_seconds(delay)

        def run_with_fixed_delay():
            while True:
                command()
                time.sleep(delay_in_seconds)

        timer = threading.Timer(initial_delay_in_seconds, run_with_fixed_delay)
        timer.start()
        return timer

def print_hello():
    print("Hello, world!")

executor = ScheduledExecutorService()
executor.schedule(print_hello, 5, TimeUnit.SECONDS)  # Prints "Hello, world!" after 5 seconds
executor.scheduleAtFixedRate(print_hello, 2, 3, TimeUnit.SECONDS)  # Prints "Hello, world!" every 3 seconds, starting after a 2-second delay
executor.scheduleWithFixedDelay(print_hello, 2, 3, TimeUnit.SECONDS)  # Similar to scheduleAtFixedRate, but waits 3 seconds between the end of one execution and the start of the next

