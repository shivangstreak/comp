from sliding_window import SlidingWindow

class UserBucket:
    def __init__(self, id):
        self.bucket = {}
        self.bucket[id] = SlidingWindow(time_window=1, bucket_capacity=5)

    def access_application(self, bucket_id, request_id):
        if bucket_id not in self.bucket:
            print("User id does not exist.")
            return
        if self.bucket[bucket_id].grant_access():
            print(f"{request_id} -- User is allowed to access the application.\n")
        else:
            print(f"{request_id} -- 429: Too many requests.\n")
