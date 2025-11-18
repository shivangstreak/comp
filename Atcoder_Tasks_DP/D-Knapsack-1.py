# https://atcoder.jp/contests/dp/tasks/dp_d

# O(n * w ) 2d solution -> did not gett accepted at atcoder
# dp[i][w] = max value using first i items with capacity w
def solve(n, w, items):
    dp = [[0] * (w+1) for _ in range(n)]
    for i in range(n):
        weight, value = items[i]
        for j in range(w+1):
            if i==0:
                # include 0th item if its weight is less than max weight allowed j
                if weight <= j:
                    dp[i][j] = max(value, dp[i][j])
                continue
            # do not include this item
            dp[i][j] = dp[i-1][j]
            # what if we try to include this item only if its weight is less than max weight allowed j
            if weight <= j:
                dp[i][j] = max(dp[i][j], dp[i-1][j-weight] + value)
    return dp[n-1][w]

# Below is also O(N·W) but 1D implementation ,No 2D indexing , No continue, No dp copying, No row/column overhead runs much faster in python3
# dp[w] = maximum value achievable with weight w after processing items seen so far


# 🚨 Danger: overwriting previous values
#
# If you do this:
#
# for w in range(weight, W+1):
#     dp[w] = max(dp[w], dp[w-weight] + value)
#
#
# You corrupt dp[w-weight] (because you're updating dp from left to right), and that allows the same item to be taken multiple times → becomes unbounded knapsack, which is WRONG.


# ✅ Fix this by iterating backwards
#
# Loop w from W down to weight:
#
# for w in range(W, weight-1, -1):
#     dp[w] = max(dp[w], dp[w-weight] + value)
#
#
# Why this works?
#
# When calculating dp[w], the term dp[w - weight]
# still refers to the previous item’s dp,
# not the updated one for current item.
#
# This ensures each item is used at most once.

# We update dp from right to left so that every item only uses previous-state DP values, ensuring each item is counted once, just like 0/1 knapsack.
def solve2(n, W, items):
    dp = [0] * (W+1)
    for weight , value in items:
        for w in range(W, weight-1, -1):
            dp[w] = max(dp[w], dp[w-weight]+ value)
    return dp[W]

if __name__ == '__main__':
    n, w= map(int, input().split())
    items = []
    for i in range(n):
        item = list(map(int, input().split()))
        items.append(item)
    print(solve2(n, w, items))