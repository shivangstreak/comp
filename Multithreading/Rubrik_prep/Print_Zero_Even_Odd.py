from threading import Lock
# https://leetcode.com/problems/print-zero-even-odd/description/

class ZeroEvenOdd:
    def __init__(self, n):
        self.n = n
        self.zero_lock = Lock()
        self.nonzero_lock = Lock()
        self.odd_lock = Lock()
        self.even_lock = Lock()
        self.nonzero_lock.acquire()
        self.even_lock.acquire()

    def zero(self, printNumber: 'Callable[[int], None]') -> None:
        for _ in range(self.n):
            self.zero_lock.acquire()
            printNumber(0)
            self.nonzero_lock.release()

    def even(self, printNumber: 'Callable[[int], None]') -> None:
        for num in range(2, self.n+1, 2):
            self.even_lock.acquire()
            self.nonzero_lock.acquire()
            printNumber(num)
            self.zero_lock.release()
            self.odd_lock.release()

    def odd(self, printNumber: 'Callable[[int], None]') -> None:
        for num in range(1, self.n+1, 2):
            self.odd_lock.acquire()
            self.nonzero_lock.acquire()
            printNumber(num)
            self.zero_lock.release()
            self.even_lock.release()