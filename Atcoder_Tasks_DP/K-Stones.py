# https://atcoder.jp/contests/dp/tasks/dp_k

if __name__ == '__main__':
    n, K = map(int, input().split())
    A = list(map(int, input().split()))

    #  Memoization
    # dp = {}
    #
    # def solve(left):
    #     if left in dp:
    #         return dp[left]
    #     dp[left] = False
    #     for a in A:
    #         if left>=a and not solve(left - a):
    #             dp[left] = True
    #             return True
    #     return dp[left]
    #
    # if solve(K):
    #     print('First')
    # else:
    #     print('Second')

    dp = [False] * (K + 1)

    for i in range(1, K + 1):
        for a in A:
            if i >= a and not dp[i - a]:
                dp[i] = True
                break

    print("First" if dp[K] else "Second")
