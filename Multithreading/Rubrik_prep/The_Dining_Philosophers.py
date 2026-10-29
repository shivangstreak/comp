from threading import Lock

class DiningPhilosophers:
    def __init__(self):
        self.forks = [Lock() for _ in range(5)]

    def wantsToEat(self,
                   philosopher: int,
                   pickLeftFork: 'Callable[[], None]',
                   pickRightFork: 'Callable[[], None]',
                   eat: 'Callable[[], None]',
                   putLeftFork: 'Callable[[], None]',
                   putRightFork: 'Callable[[], None]') -> None:
        left = philosopher
        right = (philosopher + 1) % 5

        first = min(left, right)
        second = max(left, right)

        self.forks[first].acquire()
        self.forks[second].acquire()
        try:
            pickLeftFork()
            pickRightFork()
            eat()
            putLeftFork()
            putRightFork()
        finally:
            # order of release does not matter only order of acquire matters
            self.forks[second].release()
            self.forks[first].release()

#Number the forks 0 to 4, and make every philosopher pick up the lower-numbered fork first.



# Why it can’t deadlock: philosophers 0 to 3 pick up their left fork first. Philosopher 4 has left fork 4 and right fork 0, so they pick up fork 0 first, which is the opposite direction. Now the circle is broken. If philosophers 0 to 3 each hold their left fork, philosopher 4 can’t take fork 0 (philosopher 0 has it), so philosopher 4 holds nothing. Fork 4 stays free, so philosopher 3 gets it and eats, and the chain unwinds from there.

# This is the same rule as booking several seats: always acquire multiple locks in a fixed global order. A cycle needs someone to hold a higher-numbered lock while waiting for a lower one, and ordering makes that impossible.