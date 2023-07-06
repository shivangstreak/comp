class FancyTuple:
    def __init__(self, *args):
        self._data = list(args)
        self._names = ["first", "second", "third", "fourth", "fifth"]

    def __getattr__(self, name):
        if name in self._names:
            index = self._names.index(name)
            if index < len(self._data):
                return self._data[index]
        raise AttributeError(f"'FancyTuple' object has no attribute '{name}'")

    def __len__(self):
        return len(self._data)

t = FancyTuple("dog", "cat", "bird")
print(t.first)  # Output: dog
print(t.second)  # Output: cat
print(t.third)  # Raises AttributeError

print(len(t))  # Output: 3
