#
# Here we can not do dp[w] -> maximum value achievable with weight w after processing items seen so far
# BECAUSE contraints are too high for w which is 10^9 so can not create that big array
# so we need to optimize , are per contraints we have N=100 and V=1000 atmost
# meaning we can have max sum of values as 10^5 now that big of array we can make
# so intead of creating dp[w] = maximum value achievable with weight w after processing items seen so far
# we make dp[v] = minimum weight needed to achieve value v
#
# So this is another way of solving the knapsack problem when constraints of w are too high
#
def solve(N, W, items):

    # maximum possible sum of all values
    max_value = sum(v for _, v in items)

    #INF = 10 ** 18
    INF = float('inf')
    # dp[v] = minimum weight needed to achieve value v
    dp = [INF] * (max_value + 1)
    dp[0] = 0

    for w, v in items:
        # iterate backwards to ensure 0/1 knapsack (use item at most once)
        for value in range(max_value, v - 1, -1):
            dp[value] = min(dp[value], dp[value - v] + w)

    # find the largest value that can be achieved within weight W
    ans = 0
    for value in range(max_value + 1):
        if dp[value] <= W:
            ans = value
    return ans


if __name__ == '__main__':
    n, w = map(int, input().split())
    items = []
    for i in range(n):
        item = list(map(int, input().split()))
        items.append(item)
    print(solve(n, w, items))