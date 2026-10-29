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

import threading
import random
import time

class Barrier:
    def __init__(self, n):
        self.n = n
        self.count = 0
        self.generation = 0
        self.cond = threading.Condition()

    def wait(self):
        with self.cond:
            gen = self.generation
            self.count += 1

            if self.count == self.n:          # last one to arrive
                self.generation += 1
                self.count = 0
                self.cond.notify_all()
                return True                   # this thread is the "leader"

            while gen == self.generation:
                self.cond.wait()
            return False


NUM_PLAYERS = 3
NUM_ROUNDS = 3

barrier = Barrier(NUM_PLAYERS)
# rolls[round][player] = dice value
rolls = [[0] * NUM_PLAYERS for _ in range(NUM_ROUNDS)]


def player(pid):
    for rnd in range(NUM_ROUNDS):
        time.sleep(random.uniform(0.1, 1.0))      # players think at different speeds
        rolls[rnd][pid] = random.randint(1, 6)
        print(f"  Player {pid} rolled {rolls[rnd][pid]} in round {rnd + 1}")

        is_leader = barrier.wait()                 # wait for everyone to roll

        if is_leader:                              # exactly one thread announces
            winner = max(range(NUM_PLAYERS), key=lambda p: rolls[rnd][p])
            print(f"Round {rnd + 1} done: Player {winner} wins with {rolls[rnd][winner]}\n")


threads = [threading.Thread(target=player, args=(i,)) for i in range(NUM_PLAYERS)]
for t in threads:
    t.start()
for t in threads:
    t.join()

print("Game over!")
