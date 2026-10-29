from threading import Lock, Condition
from collections import deque

class BoundedBlockingQueue(object):

    def __init__(self, capacity: int):
        self.capacity = capacity
        self.queue = deque()
        self.lock = Lock()
        self.not_full = Condition(self.lock)    # producers wait here
        self.not_empty = Condition(self.lock)   # consumers wait here

    def enqueue(self, element: int) -> None:
        self.lock.acquire()
        try:
            while len(self.queue) == self.capacity:
                self.not_full.wait()
            self.queue.append(element)
            self.not_empty.notify()             # wake one consumer
        finally:
            self.lock.release()

    def dequeue(self) -> int:
        self.lock.acquire()
        try:
            while not self.queue:
                self.not_empty.wait()
            item = self.queue.popleft()
            self.not_full.notify()              # wake one producer
            return item
        finally:
            self.lock.release()

    def size(self) -> int:
        self.lock.acquire()
        try:
            return len(self.queue)
        finally:
            self.lock.release()