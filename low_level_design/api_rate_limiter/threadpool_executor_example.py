import time
from concurrent.futures import ThreadPoolExecutor
import time
def dummy_method(id, request_id):
    print(f"{id} : {request_id}\n")
    time.sleep(2)

def main():
    #
    # This line creates a ThreadPoolExecutor context manager with 5 threads.
    # All tasks that you submit to the executor will be executed concurrently, up to 5 at a time.
    #
    with ThreadPoolExecutor(max_workers=5) as executor:
        for request_id in range(15):
            executor.submit(dummy_method, id=1, request_id=request_id)

if __name__ == "__main__":
    main()
