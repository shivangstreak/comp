import threading

DEM, REP = "D", "R"

class Bathroom:
    def __init__(self, capacity=3):
        self.capacity = capacity
        self.cond = threading.Condition()
        self.inside = 0
        self.current = None               # party inside, None if empty
        self.waiting = {DEM: 0, REP: 0}
        self.turn_party = None
        self.served_in_turn = 0

    def _other(self, p):
        return REP if p == DEM else DEM

    def _can_enter(self, party):
        if self.inside >= self.capacity:
            return False
        if self.current is not None and self.current != party:
            return False
        # fairness: yield after `capacity` entries if the other side waits
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
            if self.turn_party != party:
                self.turn_party, self.served_in_turn = party, 0
            self.served_in_turn += 1
            self.current = party
            self.inside += 1

    def exit(self, party):
        with self.cond:
            self.inside -= 1
            if self.inside == 0:
                self.current = None
            self.cond.notify_all()