if __name__ == "__main__":
    n, m = map(int, input().split())
    matrix = []
    for i in range(n):
        mat = input().strip()
        #print(mat)
        matrix.append(mat)

    dp = [[0] * m for _ in range(n)]
    MOD = 10**9+7
    for i in range(n):
        if matrix[i][0]!='.':
            break
        dp[i][0] = 1

    for j in range(m):
        if matrix[0][j]!='.':
            break
        dp[0][j] = 1

    for i in range(1, n):
        for j in range(1, m):
            if matrix[i][j]=='.':
                dp[i][j] = (dp[i-1][j]%MOD + dp[i][j-1]%MOD)%MOD

    print(dp[n-1][m-1])

# 1d optimized space

# n, m = map(int, input().split())
# matrix = [input().strip() for _ in range(n)]
#
# MOD = 10**9 + 7
#
# dp = [0] * m
#
# # initialize first row
# for j in range(m):
#     if matrix[0][j] == '#':
#         break
#     dp[j] = 1
#
# for i in range(1, n):
#     new_dp = [0] * m
#
#     # first column
#     if matrix[i][0] == '.':
#         new_dp[0] = dp[0]
#
#     for j in range(1, m):
#         if matrix[i][j] == '.':
#             new_dp[j] = (new_dp[j-1] + dp[j]) % MOD
#
#     dp = new_dp
#
# print(dp[-1])
