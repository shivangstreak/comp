from threading import Lock, Condition

class ReadWriteLock:
    def __init__(self):
        self.lock = Lock()
        self.cond = Condition(self.lock)
        self.readers = 0 # how many readers are inside right now
        self.writer = False # is a writer inside right now?
        self.waiting_writers = 0

    def acquire_read(self):
        self.lock.acquire()
        try:
            while self.writer or self.waiting_writers > 0:   # wait only if a writer is inside OR # let writers go first
                self.cond.wait()
            self.readers += 1
        finally:
            self.lock.release()

    def release_read(self):
        self.lock.acquire()
        try:
            self.readers -= 1
            if self.readers == 0:
                self.cond.notify_all() # last reader out: a writer may enter
        finally:
            self.lock.release()

    def acquire_write(self):
        self.lock.acquire()
        try:
            self.waiting_writers += 1
            while self.writer or self.readers > 0: # need the place empty
                self.cond.wait()
            self.waiting_writers -= 1
            self.writer = True
        finally:
            self.lock.release()

    def release_write(self):
        self.lock.acquire()
        try:
            self.writer = False
            self.cond.notify_all() # wake readers and writers
        finally:
            self.lock.release()

# Usage of Above ReadWriteLock
class Cache:
    def __init__(self):
        self.data = {}
        self.rw = ReadWriteLock()

    def get(self, key):
        self.rw.acquire_read()
        try:
            return self.data.get(key)     # many threads can be here at once
        finally:
            self.rw.release_read()

    def put(self, key, value):
        self.rw.acquire_write()
        try:
            self.data[key] = value        # only one thread, no readers
        finally:
            self.rw.release_write()