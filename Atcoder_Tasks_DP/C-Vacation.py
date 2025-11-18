# https://atcoder.jp/contests/dp/tasks/dp_c

def solve(n, activities):
    dp0, dp1, dp2 = activities[0][0], activities[0][1], activities[0][2]
    for i in range(1, n):
        newdp0 = activities[i][0] + max(dp1, dp2)
        newdp1 = activities[i][1] + max(dp0, dp2)
        newdp2 = activities[i][2] + max(dp0, dp1)
        dp0, dp1, dp2 = newdp0, newdp1, newdp2
    return max(dp0, dp1, dp2)

if __name__ == '__main__':
    n = int(input())
    activities = []
    for i in range(n):
        activity = list(map(int, input().split()))
        activities.append(activity)
    print(solve(n, activities))