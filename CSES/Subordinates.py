# https://cses.fi/problemset/task/1674
# Username HanzoItachi

# Given the structure of a company, your task is to calculate for each employee the number of their subordinates.
# Input
# The first input line has an integer n: the number of employees. The employees are numbered 1,2,\dots,n, and employee 1 is the general director of the company.
# After this, there are n-1 integers: for each employee 2,3,\dots,n their direct boss in the company.
# Output
# Print n integers: for each employee 1,2,\dots,n the number of their subordinates.
# Constraints
#
# 1 \le n \le 2 \cdot 10^5
#
# Example
# Input:
# 5
# 1 1 2 3
#
# Output:
# 4 1 1 0 0

import sys

sys.setrecursionlimit(300000)


def solve():
    n = int(sys.stdin.readline())
    parents = list(map(int, sys.stdin.readline().split()))

    # Build adjacency list for the tree
    tree = [[] for _ in range(n + 1)]
    for i in range(2, n + 1):
        tree[parents[i - 2]].append(i)

    # Array to store number of subordinates for each employee
    subordinates = [0] * (n + 1)

    def dfs(node):
        total = 0
        for child in tree[node]:
            total += 1 + dfs(child)  # count the child + its subordinates
        subordinates[node] = total
        return total

    dfs(1)

    # Output results for employees 1 to n
    print(' '.join(map(str, subordinates[1:])))


if __name__ == "__main__":
    solve()