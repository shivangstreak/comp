"""
Party Bathroom problem (a.k.a. "Democrats & Republicans" / Unisex Bathroom).

Rules:
  1. At most `capacity` people inside at once.
  2. Members of different parties are never inside together.
  3. No starvation: a steady stream of one party can't block the other forever.
"""
import random
import threading
import time

DEM, REP = "D", "R"


class Bathroom:
    def __init__(self, capacity: int = 3):
        self.capacity = capacity
        self.cond = threading.Condition()   # one lock + wait/notify
        self.inside = 0                     # people currently inside
        self.current = None                 # party inside now (None = empty)
        self.waiting = {DEM: 0, REP: 0}     # people queued per party
        self.turn_party = None              # party owning the current "turn"
        self.served_in_turn = 0             # entries admitted in this turn

    @staticmethod
    def _other(party):
        return REP if party == DEM else DEM

    def _can_enter(self, party) -> bool:
        if self.inside >= self.capacity:                       # rule 1
            return False
        if self.current is not None and self.current != party:  # rule 2
            return False
        # rule 3 (fairness): if the other side is waiting, this party may
        # admit at most `capacity` people in its turn, then must yield.
        if (self.waiting[self._other(party)] > 0
                and self.turn_party == party
                and self.served_in_turn >= self.capacity):
            return False
        return True

    def enter(self, party):
        with self.cond:
            self.waiting[party] += 1
            while not self._can_enter(party):
                self.cond.wait()
            self.waiting[party] -= 1

            if self.turn_party != party:      # a new turn begins
                self.turn_party = party
                self.served_in_turn = 0
            self.served_in_turn += 1
            self.current = party
            self.inside += 1

            # sanity checks (would be removed in production)
            assert self.inside <= self.capacity

    def exit(self, party):
        with self.cond:
            self.inside -= 1
            if self.inside == 0:
                self.current = None           # empty: other party may come in
            self.cond.notify_all()            # wake everyone; they re-check


# ---------------------------------------------------------------- demo / test
def person(bathroom: Bathroom, party: str, pid: int, log: list, log_lock):
    time.sleep(random.uniform(0, 0.05))
    bathroom.enter(party)
    with log_lock:
        log.append((party, pid, "in", bathroom.inside))
    time.sleep(random.uniform(0.005, 0.02))      # use the bathroom
    with log_lock:
        log.append((party, pid, "out", None))
    bathroom.exit(party)


def main():
    bathroom = Bathroom(capacity=3)
    log, log_lock = [], threading.Lock()
    threads = []
    for i in range(40):
        party = random.choice([DEM, REP])
        t = threading.Thread(target=person, args=(bathroom, party, i, log, log_lock))
        threads.append(t)
        t.start()
    for t in threads:
        t.join()

    # Verify from the log that parties never mixed and capacity held.
    inside = {}
    for party, pid, event, _ in log:
        if event == "in":
            assert all(p == party for p in inside.values()), "parties mixed!"
            inside[pid] = party
            assert len(inside) <= bathroom.capacity, "over capacity!"
            print(f"{party}{pid:02d} enters   inside={sorted(inside.values())}")
        else:
            inside.pop(pid)
    print("\nAll checks passed: no mixing, capacity respected, everyone finished.")


if __name__ == "__main__":
    main()