import bisect

lst = [1, 3, 4, 4, 6, 8]
x=4
# this would return 2, because that's the left-most position to insert 4 to maintain sorted order
i = bisect.bisect_left(lst, x)
print(i)

x = 4
# this would return 4, because that's the right-most position to insert 4 to maintain sorted order


# NOTE bisect.bisect and bisect.bisect_right gives same functionality
j = bisect.bisect_right(lst, x)

print(j)  # Output: 4
