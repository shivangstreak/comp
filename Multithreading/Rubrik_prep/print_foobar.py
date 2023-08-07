from threading import Lock, Semaphore
class FooBar:
    def __init__(self, n):
        self.n = n
        self.foo_sema = Lock() # Semaphore(1)
        self.bar_sema = Lock() # Semaphore(1)
        self.bar_sema.acquire()

    def foo(self, printFoo: 'Callable[[], None]') -> None:
        for i in range(self.n):
            self.foo_sema.acquire()
            printFoo()
            self.bar_sema.release()

    def bar(self, printBar: 'Callable[[], None]') -> None:
        for i in range(self.n):
            self.bar_sema.acquire()
            printBar()
            self.foo_sema.release()