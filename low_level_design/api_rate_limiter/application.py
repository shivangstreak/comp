from concurrent.futures import ThreadPoolExecutor
from user_bucket import UserBucket
from random import randint


def main():
    user_dict = {}
    for user_id in range(1, 10):
        user = UserBucket(id=user_id)
        user_dict[user_id] = user

    # user1 = UserBucket(id=1)
    # user_dict[1] = user1
    # user2 = UserBucket(id=2)
    # user_dict[2] = user2

    #
    # This line creates a ThreadPoolExecutor context manager with 5 threads.
    # All tasks that you submit to the executor will be executed concurrently, up to 15 at a time.
    #
    total_number_of_users = len(user_dict)

    with ThreadPoolExecutor(max_workers=5) as executor:
        for request_id in range(15):
            user_bucket_id = randint(1, total_number_of_users)
            if user_bucket_id not in user_dict:
                print(f"User id {user_bucket_id} does not exist.")
                continue
            user = user_dict[user_bucket_id]
            executor.submit(user.access_application, user_bucket_id=user_bucket_id, request_id=request_id)

if __name__ == "__main__":
    main()
