# https://atcoder.jp/contests/dp/tasks/dp_b

def solve(n, k, heights):
    dp = [float('inf')] * (n)
    dp[0] = 0
    for i in range(1, n):
        for j in range(1, k + 1):
            if j > i:
                break
            dp[i] = min(dp[i], dp[i - j] + abs(heights[i] - heights[i-j]))
    return dp[n - 1]

if __name__ == '__main__':
    n, k = map(int, input().split())
    heights = list(map(int, input().split()))
    print(solve(n, k, heights))


# O(n)

from collections import deque


def solve(n, k, heights):
    dp = [0] * n
    dq = deque([0])  # store indices

    for i in range(1, n):
        # remove indices out of range
        while dq and dq[0] < i - k:
            dq.popleft()

        dp[i] = dp[dq[0]] + abs(heights[i] - heights[dq[0]])

        # maintain deque for sliding window min
        while dq and dp[i] <= dp[dq[-1]]:
            dq.pop()
        dq.append(i)

    return dp[n - 1]