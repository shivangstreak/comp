# https://atcoder.jp/contests/dp/tasks/dp_n

# similar to https://leetcode.com/problems/minimum-cost-to-merge-stones/
if __name__ == '__main__':
    n = int(input())
    a = list(map(int, input().split()))

    k = 2

    # IN this case k=2 so it does not matter it will always have a solution but in general how to determine if there
    # is a way or not
    # N - m (k-1) = 1 where m is some +ve integer
    # Meaning after m merges after every merge k-1 piles are decreased
    # from total number of piles and in the end only 1 pile remains
    # so (n-1) should be divisible by k-1
    # if (n - 1) % (k - 1) != 0:
    #     return -1
    # dp = [[float('inf')] * n for _ in range(n)]

    dp = [[float('inf')] * n for _ in range(n)]

    prefix_sum = [0] * (n+1)
    for i in range(n):
        prefix_sum[i+1] = prefix_sum[i] + a[i]

    for l in range(1, n+1):
        for start in range(0, n-l+1):
            end = start+l-1
            if l<k:
                # we can not merge stone piles whose numbers are less than k
                dp[start][end]=0
                continue
            for mid in range(start, end, k-1):
                dp[start][end] = min(dp[start][mid] + dp[mid+1][end] , dp[start][end])
            if (l-1)%(k-1)==0:
                dp[start][end] += prefix_sum[end+1] - prefix_sum[start]

    print(dp[0][n-1])