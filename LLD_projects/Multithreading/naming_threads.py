import threading

# In this example, we are creating two separate threads and assigning each a name using the name parameter.
# We then start each thread with t.start(), and wait for all threads to complete with t.join().

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

threads = []
for i in range(2):
    t = threading.Thread(target=worker, args=(counter,), name=f'Thread-{i}')
    threads.append(t)
    t.start()

for t in threads:
    t.join()

print(f"Final counter value: {counter.value}")
