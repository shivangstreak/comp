from threading import Semaphore
from collections import deque
# https://leetcode.com/problems/design-bounded-blocking-queue/
class BoundedBlockingQueue(object):

    def __init__(self, capacity: int):
        self.queue = deque()
        # Now Whenever push happens then capacity will
        # be reduced by 1
        self.push = Semaphore(capacity)
        # Since queue is empty nothing to be popped so setting 0
        self.pop = Semaphore(0)

    def enqueue(self, element: int) -> None:
        # If push Semaphore still hase some resources left
        # Acquire it that is decrease the count of resources
        self.push.acquire()
        self.queue.append(element)
        # Now there is something to be popped to increase the count
        # of pop semaphore
        self.pop.release()

    def dequeue(self) -> int:
        self.pop.acquire()
        res = self.queue.popleft()
        # Now some things can be pushed to increase the count of push semaphore
        self.push.release()
        return res

    def size(self) -> int:
        return len(self.queue)

obj  = BoundedBlockingQueue(3)
obj.enqueue(2)
print(obj.dequeue())


