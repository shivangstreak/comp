from threading import Barrier, Semaphore
class H2O:
    def __init__(self):
        self.bar = Barrier(3)
        self.semaphore_oxygen = Semaphore(1)
        self.semaphore_hydrogen = Semaphore(2)

    def hydrogen(self, releaseHydrogen: 'Callable[[], None]') -> None:
        self.semaphore_hydrogen.acquire()
        self.bar.wait()
        # releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen()
        self.semaphore_hydrogen.release()


    def oxygen(self, releaseOxygen: 'Callable[[], None]') -> None:
        self.semaphore_oxygen.acquire()
        self.bar.wait()
        # releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen()
        self.semaphore_oxygen.release()