# HOW TO HANDLE HOT KEY WRITES
class StripedStore:
    def __init__(self, num_stripes=16):
        self.n = num_stripes
        self.shards = [{} for _ in range(num_stripes)]
        self.locks = [threading.Lock() for _ in range(num_stripes)]
        self.hot_keys = {}                       # key -> number of splits

    def _index(self, key):
        return hash(key) % self.n

    def mark_hot(self, key, splits=8):
        self.hot_keys[key] = splits

    def incr(self, key, amount=1):
        if key in self.hot_keys:
            # Salt: add a random suffix so writes spread across stripes
            key = f"{key}#{random.randrange(self.hot_keys[key])}"
        i = self._index(key)
        with self.locks[i]:
            self.shards[i][key] = self.shards[i].get(key, 0) + amount

    def get_count(self, key):
        if key in self.hot_keys:
            # Read every sub-key and add them up
            parts = [f"{key}#{p}" for p in range(self.hot_keys[key])]
        else:
            parts = [key]
        total = 0
        for k in parts:
            i = self._index(k)
            with self.locks[i]:
                total += self.shards[i].get(k, 0)
        return total


store = StripedStore()
store.mark_hot("requests", splits=8)

def worker():
    for _ in range(10_000):
        store.incr("requests")

threads = [threading.Thread(target=worker) for _ in range(8)]
for t in threads: t.start()
for t in threads: t.join()

print(store.get_count("requests"))   # 80000