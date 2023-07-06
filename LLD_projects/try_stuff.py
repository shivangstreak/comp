# class Person:
#     def __init__(self, name):
#         self.name = name
#     def __repr__(self):
#         return f"Person ({self.name})"
#
# p = Person("tim")
# print(dir(p))
# print(p)
#

import inspect
from collections import deque
from queue import Queue
a = [1,2,3]
de = deque(a)
de.appendleft(-1)
print(de)

print(inspect.getsource(Queue))
