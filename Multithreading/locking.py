from concurrent.futures import ThreadPoolExecutor
import threading

class Counter:
    def __init__(self):
        self.value = 0
        self.lock = threading.Lock()

    def increment(self):
        with self.lock:
            self.value += 1
            print(f"Thread {threading.current_thread().name} increased counter to {self.value}")


def worker(counter):
    for _ in range(100):
        counter.increment()

counter = Counter()

with ThreadPoolExecutor(max_workers=2) as executor:
    for _ in range(2):
        executor.submit(worker, counter)

print(f"Final counter value: {counter.value}")
