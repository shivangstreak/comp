from queue import Queue

q =Queue()

q.put(2)
q.put(3)
q.put(4)
q.put(5)


while not q.empty():
    print(q.get())


from collections import deque

# Create a new deque
my_deque = deque()

# Append elements to the right end
my_deque.append("First")
my_deque.append("Second")
my_deque.append("Third")

# Append elements to the left end
my_deque.appendleft("Zero")
my_deque.appendleft("Minus One")

# Access elements
print("Elements in deque:", my_deque)

# Remove elements from the right end
item1 = my_deque.pop()
item2 = my_deque.pop()

# Remove elements from the left end
item3 = my_deque.popleft()
item4 = my_deque.popleft()

# Access elements after removal
print("Remaining elements in deque:", my_deque)


import queue

# Create a new priority queue
my_queue = queue.PriorityQueue()

# Add elements with priorities
my_queue.put((3, "Third"))
my_queue.put((1, "First"))
my_queue.put((2, "Second"))

# Get and remove elements from the priority queue
item1 = my_queue.get()
item2 = my_queue.get()

# Check the remaining items in the priority queue
print("Remaining items in the priority queue:")
while not my_queue.empty():
    item = my_queue.get()
    print(item)


import queue

# Create a new min priority queue
min_queue = queue.PriorityQueue()

# Add elements with priorities
min_queue.put(3)
min_queue.put(1)
min_queue.put(2)

# Get and remove elements from the min priority queue
item1 = min_queue.get()
item2 = min_queue.get()

# Check the remaining items in the min priority queue
print("Remaining items in the min priority queue:")
while not min_queue.empty():
    item = min_queue.get()
    print(item)
