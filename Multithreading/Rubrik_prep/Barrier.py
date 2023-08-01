# In this example, we create a Barrier object with n=3,
# meaning that we want 3 threads to wait at the barrier before they can proceed.
# The thread_function is the target function for each thread, and it simply waits at the barrier and then proceeds.
# When all 3 threads reach the barrier, they are released together, and their execution continues.
# The output should show that the threads are waiting at the barrier and proceeding together once all of them have arrived.

import threading

# Create a Barrier with 3 threads required to wait
barrier = threading.Barrier(3)

def thread_function(thread_id):
    print(f"Thread {thread_id} is ready.")
    # Wait at the barrier
    barrier.wait()
    print(f"Thread {thread_id} is proceeding.")

if __name__ == "__main__":
    threads = []

    # Create and start 3 threads
    for i in range(3):
        thread = threading.Thread(target=thread_function, args=(i,))
        threads.append(thread)
        thread.start()

    # Wait for all threads to finish
    for thread in threads:
        thread.join()

    print("All threads have finished execution.")
