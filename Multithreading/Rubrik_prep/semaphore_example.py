import threading
import time

# The shared resource
shared_resource = []
MAX_ALLOWED_THREADS = 2

# Create a Semaphore with the maximum number of allowed threads
semaphore = threading.Semaphore(MAX_ALLOWED_THREADS)

def thread_function(thread_id):
    global shared_resource

    # Acquire the semaphore before accessing the shared resource
    semaphore.acquire()

    try:
        # Critical section: Accessing the shared resource
        shared_resource.append(thread_id)
        print(f"Thread {thread_id} is accessing the shared resource: {shared_resource}")
        time.sleep(2)

    finally:
        # Release the semaphore after accessing the shared resource
        semaphore.release()

if __name__ == "__main__":
    threads = []

    # Create and start multiple threads
    for i in range(5):
        thread = threading.Thread(target=thread_function, args=(i,))
        threads.append(thread)
        thread.start()

    # Wait for all threads to finish
    for thread in threads:
        thread.join()

    print("All threads have finished execution.")
