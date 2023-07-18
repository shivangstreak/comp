import time
import queue
from collections import deque

class SlidingWindow:
    def __init__(self, time_window_size, number_of_api_request_capacity_per_window):
        self.time_window_size = time_window_size
        self.number_of_api_request_capacity_per_window = number_of_api_request_capacity_per_window
        self.window = queue.Queue()

    def grant_access(self):
        current_time = time.time() * 1000

        if self.window.qsize() < self.number_of_api_request_capacity_per_window:
            self.window.put(current_time)
            return True

        # Pop elements in queue till size of this window is less than the number_of_api_request_capacity_per_window
        self.check_and_update_window(current_time)

        if self.window.qsize() < self.number_of_api_request_capacity_per_window:
            self.window.put(current_time)
            return True

        return False

    def check_and_update_window(self, current_time):
        while not self.window.empty():
            calculate_time = (current_time - self.window.queue[0]) / 1000
            if calculate_time < self.time_window_size:
                break
            else:
                # Pop the front of the queue
                self.window.get()