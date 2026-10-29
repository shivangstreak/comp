import threading


class Event:
    def __init__(self):
        self._callbacks = []
        self._fired = False
        self._lock = threading.Lock()

    def register_callback(self, cb):
        with self._lock:
            if not self._fired:
                self._callbacks.append(cb)
                return
        # Event already fired: invoke immediately (outside the lock)
        self._safe_call(cb)

    def event_fired(self):
        with self._lock:
            if self._fired:          # idempotent
                return
            self._fired = True
            to_call = self._callbacks
            self._callbacks = []     # release references
        # Call outside the lock so a callback can safely call register_callback
        for cb in to_call:
            self._safe_call(cb)

    @staticmethod
    def _safe_call(cb):
        try:
            cb()
        except Exception as e:        # one bad listener must not break others
            print(f"callback {cb} failed: {e}")


# Demo matching the diagram
if __name__ == "__main__":
    ev = Event()
    ev.register_callback(lambda: print("cb1"))
    ev.register_callback(lambda: print("cb2"))
    ev.event_fired()                          # prints cb1, cb2
    ev.register_callback(lambda: print("cb3"))  # prints cb3 immediately