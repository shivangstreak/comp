from sliding_window import SlidingWindow

class UserBucket:
    user_bucket = {}
    def __init__(self, id):
        self.user_id = id
        #self.bucket = {}
        #self.bucket[id] = SlidingWindow(time_window_size=1, number_of_api_request_capacity_per_window=5)
        UserBucket.user_bucket[id] = SlidingWindow(time_window_size=1, number_of_api_request_capacity_per_window=5)


    def access_application(self, user_bucket_id, request_id):
        if user_bucket_id not in UserBucket.user_bucket:
            print(f"User id {user_bucket_id} does not exist.")
            return
        if UserBucket.user_bucket[user_bucket_id].grant_access():
            print(f"{request_id} -- User {self.user_id} is allowed to access the application.\n")
        else:
            print(f"{request_id} -- 429: Too many requests for user {self.user_id}\n")
