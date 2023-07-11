from concurrent.futures import ThreadPoolExecutor
from user_bucket import UserBucket

def main():
    user_bucket = UserBucket(id=1)
    #
    # This line creates a ThreadPoolExecutor context manager with 5 threads.
    # All tasks that you submit to the executor will be executed concurrently, up to 15 at a time.
    #
    with ThreadPoolExecutor(max_workers=10) as executor:
        for request_id in range(15):
            executor.submit(user_bucket.access_application, bucket_id=1, request_id=request_id)

if __name__ == "__main__":
    main()
