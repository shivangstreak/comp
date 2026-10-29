from threading import Semaphore, Lock

class H2O:
    def __init__(self):
        self.h_sem = Semaphore(2)    # hydrogen slots for the current molecule
        self.o_sem = Semaphore(0)    # counts hydrogens that have been released
        self.o_lock = Lock()         # only one oxygen collects hydrogens at a time

    def hydrogen(self, releaseHydrogen: 'Callable[[], None]') -> None:
        self.h_sem.acquire()         # take one of the 2 H slots
        releaseHydrogen()
        self.o_sem.release()         # tell oxygen "one H is done"

    def oxygen(self, releaseOxygen: 'Callable[[], None]') -> None:
        self.o_lock.acquire()
        try:
            self.o_sem.acquire()     # wait for first H
            self.o_sem.acquire()     # wait for second H
            releaseOxygen()
            self.h_sem.release()     # open 2 H slots for the next molecule
            self.h_sem.release()
        finally:
            self.o_lock.release()

# USING CONDITIONAL VARIABLES

from threading import Lock, Condition

class H2O:
    def __init__(self):
        self.lock = Lock()
        self.cond = Condition(self.lock)
        self.h = 0        # hydrogens in the current molecule
        self.o = 0        # oxygens in the current molecule

    def hydrogen(self, releaseHydrogen: 'Callable[[], None]') -> None:
        self.lock.acquire()
        try:
            while self.h == 2:                # molecule already has 2 H
                self.cond.wait()
            releaseHydrogen()
            self.h += 1
            self._finish_if_complete()
        finally:
            self.lock.release()

    def oxygen(self, releaseOxygen: 'Callable[[], None]') -> None:
        self.lock.acquire()
        try:
            while self.o == 1:                # molecule already has 1 O
                self.cond.wait()
            releaseOxygen()
            self.o += 1
            self._finish_if_complete()
        finally:
            self.lock.release()

    def _finish_if_complete(self):            # called while holding the lock
        if self.h == 2 and self.o == 1:
            self.h = 0
            self.o = 0
            self.cond.notify_all()            # start the next molecule