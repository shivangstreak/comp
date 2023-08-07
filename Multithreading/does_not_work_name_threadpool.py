from concurrent.futures import ThreadPoolExecutor
import threading

# However, note that the ThreadPoolExecutor may reuse threads for
# multiple tasks, so the names you set may not correspond to the actual
# threads that execute the tasks. If you want to ensure that each task is executed by a
# separate thread with a specific name, you might want to use the threading.Thread class directly:

# please see naming_threads_with_locking.py file to looking for mentioned implementation.

#Todo THIS CODE DOES NOT WORK


class Counter:
    def __init__(self):
        self.value = 0
        self.lock = threading.Lock()

    def increment(self):
        with self.lock:
            self.value += 1
            print(f"{threading.current_thread().name} increased counter to {self.value}")

def worker(counter):
    for _ in range(100):
        counter.increment()

counter = Counter()

with ThreadPoolExecutor(max_workers=2) as executor:
    for i in range(2):
        # Submit a new task and set the thread name

        #TODO set_name is not available in ThreadPoolExecutor so do not refer to this wrong code this fails
        executor.submit(worker, counter).set_name(f'Thread-{i}')

print(f"Final counter value: {counter.value}")
