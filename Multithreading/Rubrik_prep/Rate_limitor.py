import time
from collections import deque

class RateLimiter:
    def __init__(self, capacity):
        self.capacity = capacity
        self.requests = deque()

    def canAccept(self, expireTime):
        current_time = time.time()

        # Cleanup expired requests
        while self.requests and self.requests[0] <= current_time:
            self.requests.popleft()

        # Check if we can accept more requests
        if len(self.requests) < self.capacity:
            self.requests.append(current_time + expireTime)
            return True

        return False

import threading

class ConcurrentRateLimiter(RateLimiter):
    def __init__(self, capacity):
        super().__init__(capacity)
        self.lock = threading.Lock()

    def canAccept(self, expireTime):
        with self.lock:
            return super().canAccept(expireTime)

import threading
import time

def make_request(rate_limiter, expire_time):
    if rate_limiter.canAccept(expire_time):
        print(f"Request accepted by {threading.current_thread().name}")
    else:
        print(f"Request rejected by {threading.current_thread().name}")


if __name__ == "__main__":
    rate_limiter = ConcurrentRateLimiter(5)  # limit of 5 requests
    expire_time = 2  # 2 seconds

    threads = []
    for i in range(10):  # create 10 threads
        t = threading.Thread(target=make_request, args=(rate_limiter, expire_time), name=f"Thread-{i}")
        t.start()
        threads.append(t)

    # Wait for all threads to finish
    for t in threads:
        t.join()



