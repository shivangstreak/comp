# https://atcoder.jp/contests/dp/tasks/dp_m

if __name__ == '__main__':
    n, k = map(int, input().split())
    a = list(map(int, input().split()))

    #dp[i][j] = number of ways to distribute j candies to i children
    # dp = [[0] * (k+1) for _ in range(n+1)]
    # dp[0][0] =  1 # zero candies among zero children has only 1 way
    # MOD = 10**9+7
    # for i in range(1, n+1):
    #     ai=a[i-1]
    #     prefix_sum = [0] * (k+1)
    #     prefix_sum[0] = dp[i-1][0]
    #     for j in range(1,k+1):
    #         prefix_sum[j] = (prefix_sum[j-1] + dp[i-1][j]) % MOD
    #     for j in range(0, k+1):
    #         dp[i][j] = prefix_sum[j]
    #         if j-ai-1>=0:
    #             dp[i][j] = (prefix_sum[j] - prefix_sum[j-ai-1]) %MOD
    #
    # print(dp[n][k]%MOD)

    #dp[j] -> number of ways for current i children to sum to j

    dp = [0] * (k+1)
    dp[0]=1 # zero candies among zero children
    MOD = 10**9 + 7
    for i in range(1, n+1):
        ai=a[i-1]
        prefix_sum = [0] * (k+1)
        prefix_sum[0] = dp[0]
        for j in range(1,k+1):
            prefix_sum[j] = (prefix_sum[j-1] + dp[j]) % MOD
        dp2 = [0] * (k+1)
        for j in range(0,k+1):
            dp2[j] = prefix_sum[j]
            if j - ai - 1 >= 0:
                dp2[j] = (prefix_sum[j] - prefix_sum[j - ai - 1]) % MOD
        dp = dp2

    print(dp[k]%MOD)