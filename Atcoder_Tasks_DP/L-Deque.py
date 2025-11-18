# https://atcoder.jp/contests/dp/tasks/dp_l

if __name__ == "__main__":
    n = int(input())
    a = list(map(int, input().split()))
    N=n
    # dp = [[0]* n for _ in range(n)]
    #
    # for i in range(n):
    #     dp[i][i]=a[i]
    #
    # for l in range(2, n+1):
    #     for start in range(0, n-l+1):
    #         end = start+l-1
    #         left_choice = a[start] - dp[start+1][end]
    #         right_choice = a[end] - dp[start][end-1]
    #         dp[start][end] = max(left_choice, right_choice)
    #
    # print(dp[0][n-1])


    dp = [0] * N
    for i in range(N):
        dp[i] = a[i]
    for length in range(2, N + 1):
        # new_dp[i] will store dp[i][i+length-1]
        new_dp = [0] * (N - length + 1)
        for i in range(0, N - length + 1):
            j = i + length - 1
            new_dp[i] = max(a[i] - dp[i + 1],
                            a[j] - dp[i])
        dp = new_dp
    print(dp[0])
