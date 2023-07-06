import heapq

class ElementWrapper:
    def __init__(self, element):
        self.element = element

    def __lt__(self, other):
        # Custom comparison logic for the elements
        return self.element > other.element

nums = [4, 2, 7, 1, 5]
wrapped_nums = [ElementWrapper(x) for x in nums]
heapq.heapify(wrapped_nums)
max_heap = [x.element for x in wrapped_nums]

print(max_heap)  # Output: [7, 5, 4, 1, 2]

