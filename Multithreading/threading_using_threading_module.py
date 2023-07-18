import threading
import time


def dummy_method(id, request_id):
    print(f"{threading.current_thread().name}: {id} : {request_id}\n")
    time.sleep(2)


def main():
    threads = []
    for request_id in range(15):
        # create a new thread for each request
        thread = threading.Thread(target=dummy_method, args=(1, request_id), name=f"Thread-name{request_id}")
        threads.append(thread)

    # start 5 threads at a time
    for i in range(0, len(threads), 5):
        # start threads
        for thread in threads[i:i + 5]:
            thread.start()

        # wait for these threads to complete
        for thread in threads[i:i + 5]:
            thread.join()


if __name__ == "__main__":
    main()
