import time
import concurrent.futures
from typing import Callable

class NonBlockingRunner:
    def __init__(self):
        self.executor = concurrent.futures.ThreadPoolExecutor(max_workers=10)

    def run_after_delay(self, runnable: Callable[[], None], wait_time: int):
        # Wrapping the runnable into another function that sleeps before executing the original function
        def delayed_run():
            time.sleep(wait_time)
            runnable()

        # Submit the new function to the thread pool
        self.executor.submit(delayed_run)

def test_run():
    print("Test run started")

# Create a runner instance
runner = NonBlockingRunner()

# Run the function after 5 seconds
runner.run_after_delay(test_run, 5)

print("This prints immediately")



# Using threading module

import time
import threading
from typing import Callable

class NonBlockingRunner:
    def __init__(self):
        pass

    def run_after_delay(self, runnable: Callable[[], None], wait_time: int):
        # Wrapping the runnable into another function that sleeps before executing the original function
        def delayed_run():
            time.sleep(wait_time)
            runnable()

        # Create a new Thread
        thread = threading.Thread(target=delayed_run)

        # Start the Thread
        thread.start()


def test_run():
    print("Test run started")

# Create a runner instance
runner = NonBlockingRunner()

# Run the function after 5 seconds
runner.run_after_delay(test_run, 5)

print("This prints immediately")
