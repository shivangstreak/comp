from collections import deque

INF = float("inf")


# One record per successful add. A remove only stamps removed_at.
class Node:
    def __init__(self, val, added_at):
        self.val = val
        self.added_at = added_at
        self.removed_at = INF       # INF = still in the set
        self.prev = None
        self.next = None


class SnapshotIterator:
    def __init__(self, owner, start, snap_time):
        self.owner = owner          # the set, so we can tell it when we finish
        self.cur = start            # last node we've passed (starts at dummy head)
        self.snap_time = snap_time  # the moment this snapshot was taken
        self.done = False

    def visible(self, node):
        # Was this value in the set at snap_time?
        return node.added_at <= self.snap_time < node.removed_at

    def has_next(self):
        node = self.cur.next
        while node is not None and node.added_at <= self.snap_time:
            if self.visible(node):
                return True
            self.cur = node         # removed before our snapshot: skip it for good
            node = node.next
        # Reached the end, or a node newer than our snapshot -> finished.
        if not self.done:
            self.done = True
            self.owner.iterator_finished()
        return False

    def next(self):
        self.has_next()             # moves cur up to just before the next visible node
        self.cur = self.cur.next
        return self.cur.val


class SnapshotSet:
    def __init__(self):
        self.head = Node(None, 0)   # dummy head, never removed
        self.tail = self.head
        self.nodes = {}             # value -> its current live node
        self.time = 0               # ticks on every successful add / remove

        # Only needed for cleanup:
        self.iters = deque()        # iterators in creation order (oldest first)
        self.waiting = deque()      # removed nodes an old iterator may still need

    # ---------- basic set operations: O(1) ----------
    def add(self, val):
        if val in self.nodes:
            return False
        self.time += 1
        node = Node(val, self.time)
        node.prev = self.tail       # append at the tail = insertion order
        self.tail.next = node
        self.tail = node
        self.nodes[val] = node
        return True

    def remove(self, val):
        if val not in self.nodes:
            return False
        self.time += 1
        node = self.nodes.pop(val)
        node.removed_at = self.time

        # Cleanup rule 1: if no live iterator can see this node, unlink it now.
        newest_snap = self.iters[-1].snap_time if self.iters else -1
        if node.added_at > newest_snap:
            self.unlink(node)
        else:
            self.waiting.append(node)   # keep it for the old iterators
        return True

    def contains(self, val):
        return val in self.nodes

    # ---------- snapshot: O(1), nothing is copied ----------
    def iterator(self):
        it = SnapshotIterator(self, self.head, self.time)
        self.iters.append(it)
        return it

    # ---------- cleanup ----------
    def unlink(self, node):
        node.prev.next = node.next
        if node.next:
            node.next.prev = node.prev
        else:
            self.tail = node.prev
        # node.next is left as is, so an iterator sitting on this node can still move forward.

    def iterator_finished(self):
        # Cleanup rule 2: drop finished iterators from the front...
        while self.iters and self.iters[0].done:
            self.iters.popleft()
        oldest_snap = self.iters[0].snap_time if self.iters else INF
        # ...then any node removed by the oldest live snapshot is invisible to everyone.
        while self.waiting and self.waiting[0].removed_at <= oldest_snap:
            self.unlink(self.waiting.popleft())


def solution(operations, args):
    s = SnapshotSet()
    iters = []                      # handle = position in this list
    out = []
    for op, a in zip(operations, args):
        if op == "add":
            out.append(int(s.add(a[0])))
        elif op == "remove":
            out.append(int(s.remove(a[0])))
        elif op == "contains":
            out.append(int(s.contains(a[0])))
        elif op == "iterator":
            iters.append(s.iterator())
            out.append(len(iters) - 1)
        elif op == "has_next":
            out.append(int(iters[a[0]].has_next()))
        elif op == "next":
            out.append(iters[a[0]].next())
    return out