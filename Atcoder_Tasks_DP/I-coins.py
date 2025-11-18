# Using n^2 2D dp
# if __name__ == '__main__':
#     n = int(input())
#     probabilities = list(map(float, input().split()))
#     # dp[i][j] = probability of having j heads using first i coins
#     dp = [[0.0] * (n+1) for _ in range(n+1)]
#     dp[0][0] = 1.0 # probability of having 0 heads with 0 coins is 1.0
#     for i in range(1, n+1):
#         p = probabilities[i-1]
#         for h in range(0, i+1):
#             # if last coin is tails
#             dp[i][h] = dp[i-1][h] * (1-p)
#             # if current coin is heads
#             if h>0:
#                 dp[i][h]+=dp[i-1][h-1] * p
#
#     ans = 0.0
#     # we need atleast n//2+1 head coins to have more heads than tails.
#     for j in range(n//2+1 , n+1):
#         ans+=dp[n][j]
#     print(ans)

# Using 2 row dp
# if __name__ == '__main__':
#     n = int(input())
#     probabilities = list(map(float, input().split()))
#     # prev_dp[j] = probability of having j heads using first i coins
#     # in this case prev_dp is for first row that is 0th row , 0 coins
#     prev_dp = [0.0] * (n+1)
#     prev_dp[0] = 1.0 #probability of having 0 heads with 0 coins is 1.0
#     for i in range(1, n+1):
#         p = probabilities[i - 1]
#         curr_dp = [0.0] * (n + 1)
#         for h in range(0, i+1):
#             # last coin is tails
#             curr_dp[h] = prev_dp[h] * (1-p)
#             # last coin in heads
#             if h>0:
#                 curr_dp[h]+= prev_dp[h-1] * p
#         prev_dp = curr_dp
#
#     ans = 0.0
#     for j in range(n//2+1, n+1):
#         ans+=prev_dp[j]
#     print(ans)

# 1D DP
if __name__ == "__main__":
    n = int(input())
    probabilities = list(map(float, input().split()))
    # dp[h] = probability of exactly h heads after processing some prefix
    dp = [0.0] * (n+1)
    dp[0] = 1.0 # probability of 0 coins making 0 heads is 1.0
    for i in range(1, n+1):
        p = probabilities[i - 1]
        # update from high h -> low h
        for h in range(i, -1 , -1):
            # last coin is tails
            dp[h] = dp[h] * (1-p)
            # last coin is heads
            if h>0:
                dp[h]+=dp[h-1] * p

    need = n // 2 + 1
    answer = sum(dp[need:])   # probability heads > tails
    print(answer)