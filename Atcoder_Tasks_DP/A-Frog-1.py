# Question link
# https://atcoder.jp/contests/dp/tasks/dp_a


# O(n) space
def solve(n, height):
    #n = len(height)
    dp = [0]* n
    dp[0] = 0
    dp[1] = dp[0]+ abs(height[1]-height[0])
    for i in range(2, n):
        dp[i] = min(dp[i-1] + abs(height[i]-height[i-1]), dp[i-2]+ abs(height[i]-height[i-2]))
    return dp[n-1]

# O(1) space
def solve2(n, height):
    dp_two_steps_away = 0
    dp_one_steps_away = dp_two_steps_away + abs(height[1]-height[0])
    for i in range(2, n):
        temp_dp = min(dp_one_steps_away + abs(height[i]-height[i-1]), dp_two_steps_away+ abs(height[i]-height[i-2]))
        dp_two_steps_away = dp_one_steps_away
        dp_one_steps_away = temp_dp
    return dp_one_steps_away
if __name__ == '__main__':
    n = int(input())
    height = list(map(int, input().split()))
    print(solve2(n, height))