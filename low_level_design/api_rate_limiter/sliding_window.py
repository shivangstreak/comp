import time
import queue

class SlidingWindow:
    def __init__(self, time_window, bucket_capacity):
        self.time_window = time_window
        self.bucket_capacity = bucket_capacity
        self.window = queue.Queue()

    def grant_access(self):
        current_time = time.time() * 1000
        if self.window.qsize() < self.bucket_capacity:
            self.window.put(current_time)
            return True
        self.check_and_update_window(current_time)
        if self.window.qsize() < self.bucket_capacity:
            self.window.put(current_time)
            return True
        return False

    def check_and_update_window(self, current_time):
        while not self.window.empty():
            calculate_time = (current_time - self.window.queue[0]) / 1000
            if calculate_time < self.time_window:
                break
            else:
                self.window.get()