from threading import Lock

# https://leetcode.com/problems/the-dining-philosophers/description/

class DiningPhilosophers:
    def __init__(self):
        self.forks = [Lock() for _ in range(5)]

    # call the functions directly to execute, for example, eat()
    def wantsToEat(self,
                   philosopher: int,
                   pickLeftFork: 'Callable[[], None]',
                   pickRightFork: 'Callable[[], None]',
                   eat: 'Callable[[], None]',
                   putLeftFork: 'Callable[[], None]',
                   putRightFork: 'Callable[[], None]') -> None:

        left_fork, right_fork = self.forks[philosopher], self.forks[philosopher - 1]

        # for even philosopers pick first left then right, for odd - first right then left
        if philosopher % 2:
            first_fork, second_fork = right_fork, left_fork
        else:
            first_fork, second_fork = left_fork, right_fork

        with first_fork, second_fork:
            pickLeftFork()
            pickRightFork()
            eat()
            putRightFork()
            putLeftFork()