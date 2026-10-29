import random
import threading
import threading


class StripedKVStore:
    def __init__(self, num_stripes: int = 16):
        if num_stripes <= 0:
            raise ValueError("num_stripes must be positive")
        self._num_stripes = num_stripes
        # One dict + one lock per stripe
        self._shards = [{} for _ in range(num_stripes)]
        self._locks = [threading.Lock() for _ in range(num_stripes)]

    def _index(self, key: str) -> int:
        # Same key -> same number -> same stripe, every time.
        return hash(key) % self._num_stripes

    def put(self, key: str, value) -> None:
        i = self._index(key)
        with self._locks[i]:
            self._shards[i][key] = value

    def get(self, key: str):
        i = self._index(key)
        with self._locks[i]:
            return self._shards[i].get(key)    # None if absent

    def delete(self, key: str) -> None:
        i = self._index(key)
        with self._locks[i]:
            self._shards[i].pop(key, None)     # no error if missing

    def put_if_absent(self, key: str, value):
        # Check and insert under ONE lock, so no other thread can sneak in between
        i = self._index(key)
        with self._locks[i]:
            shard = self._shards[i]
            if key in shard:
                return shard[key]
            shard[key] = value
            return None

    def size(self) -> int:
        # Lock ALL stripes, always in the same order to avoid deadlock
        for lock in self._locks:
            lock.acquire()
        try:
            return sum(len(shard) for shard in self._shards)
        finally:
            for lock in reversed(self._locks):
                lock.release()


def run_threads(target, num_threads, *args):
    """Start num_threads threads together, wait for all to finish."""
    barrier = threading.Barrier(num_threads)

    def wrapped(thread_id):
        barrier.wait()              # all threads start at the same moment
        target(thread_id, *args)

    threads = [threading.Thread(target=wrapped, args=(t,)) for t in range(num_threads)]
    for t in threads:
        t.start()
    for t in threads:
        t.join(timeout=30)
        assert not t.is_alive(), "thread hung: possible deadlock"


def main():
    # ---------- 1. Basic single-threaded behaviour ----------
    print("1. Basic operations")
    store = StripedKVStore(num_stripes=8)
    store.put("apple", 10)
    store.put("banana", 20)
    print("   get(apple)  =", store.get("apple"))     # 10
    store.put("apple", 11)                             # overwrite
    print("   overwrite   =", store.get("apple"))     # 11
    store.delete("apple")
    print("   after delete=", store.get("apple"))     # None
    store.delete("missing")                            # no error
    print("   size        =", store.size())           # 1
    assert store.get("banana") == 20 and store.size() == 1

    # ---------- 2. Many threads, different keys: nothing lost ----------
    print("2. 8 threads x 5,000 puts on different keys")
    store = StripedKVStore()
    keys_per_thread = 5_000

    def writer(tid):
        for k in range(keys_per_thread):
            store.put(f"t{tid}-k{k}", k)

    run_threads(writer, 8)
    print("   size =", store.size(), "(expected 40000)")
    assert store.size() == 8 * keys_per_thread
    assert store.get("t3-k1234") == 1234

    # ---------- 3. Many threads, SAME key: no corruption ----------
    print("3. 8 threads overwriting the same key")
    store = StripedKVStore()

    def same_key_writer(tid):
        for _ in range(5_000):
            store.put("shared", tid)

    run_threads(same_key_writer, 8)
    final = store.get("shared")
    print("   final value =", final, "(must be one of the thread ids 0-7)")
    assert final in range(8)

    # ---------- 4. put_if_absent race: exactly one winner ----------
    print("4. 8 threads race put_if_absent on one key")
    store = StripedKVStore()
    winners = []
    winners_lock = threading.Lock()

    def racer(tid):
        if store.put_if_absent("leader", tid) is None:   # None means "I inserted it"
            with winners_lock:
                winners.append(tid)

    run_threads(racer, 8)
    print("   winners =", winners, "| stored =", store.get("leader"))
    assert len(winners) == 1 and store.get("leader") == winners[0]

    # ---------- 5. Mixed put / get / delete: no crash, no hang ----------
    print("5. Mixed random put/get/delete on a small key set")
    import random
    store = StripedKVStore()

    def mixed(tid):
        for _ in range(20_000):
            key = f"k{random.randrange(10)}"          # tiny key set -> lots of collisions
            op = random.random()
            if op < 0.4:
                store.put(key, tid)
            elif op < 0.8:
                store.get(key)
            else:
                store.delete(key)

    run_threads(mixed, 8)
    print("   size =", store.size(), "(anything from 0 to 10 is valid)")
    assert 0 <= store.size() <= 10

    print("\nAll checks passed.")


if __name__ == "__main__":
    main()
