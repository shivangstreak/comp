import threading

class Events:
    def __init__(self):
        self._call_backs = []
        self._event_called = False
        self._lock = threading.Lock()

    def event_run(self):
        with self._lock:
            self._event_called = True
            to_call = self._call_backs
            self._call_backs = []
            for cb in to_call:
                self._safe_calls(cb)
            return

    def register_call_backs(self, cb):
        with self._lock:
            if not self._event_called:
                self._call_backs.append(cb)
                return
        # Since event was called before so we should call this immediately  
        self._safe_calls(cb)

    def _safe_calls(self, cb):
        try:
            cb()
        except Exception as ex:
            print(f'Exception has occured {ex}')

if __name__ == '__main__':
    ev = Events()

