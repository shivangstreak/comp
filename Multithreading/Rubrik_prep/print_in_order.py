from threading import Lock, Semaphore

class Foo:
    def __init__(self):
        self.firstJobDone = Semaphore(1)
        self.secondJobDone = Semaphore(1)
        self.firstJobDone.acquire()
        self.secondJobDone.acquire()

    def first(self, printFirst: 'Callable[[], None]') -> None:
        # printFirst() outputs "first".
        printFirst()
        # Notify the thread that is waiting for the first job to be done.
        self.firstJobDone.release()

    def second(self, printSecond: 'Callable[[], None]') -> None:
        # Wait for the first job to be done
        self.firstJobDone.acquire()
        # printSecond() outputs "second".
        printSecond()
        self.firstJobDone.release()
        # Notify the thread that is waiting for the second job to be done.
        self.secondJobDone.release()

    def third(self, printThird: 'Callable[[], None]') -> None:
        # Wait for the second job to be done.
        self.secondJobDone.acquire()
        # printThird() outputs "third".
        printThird()
        self.secondJobDone.release()