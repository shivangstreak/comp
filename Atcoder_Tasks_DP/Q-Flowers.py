import sys
input = sys.stdin.readline

# Fenwick Tree for prefix maximum
class FenwickMax:
    def __init__(self, n):
        self.n = n
        self.bit = [0] * (n + 1)

    def update(self, i, value):
        while i <= self.n:
            self.bit[i] = max(self.bit[i], value)
            # To get next
            # 1 ) 2's complement to get minus of index
            # 2 ) AND this with index this will give LSB (Least significant bit)
            # 3 ) ADD it to index
            i += i & -i

    def query(self, i):
        """returns max on range [1..i]"""
        res = 0
        while i > 0:
            res = max(res, self.bit[i])
            # To get parent
            # 1 ) 2's complement to get minus of index
            # 2 ) AND this with index this will give LSB (Least significant bit)
            # 3 ) Substract that from index
            i -= i & -i
        return res


def solve():
    N = int(input())
    h = list(map(int, input().split()))
    a = list(map(int, input().split()))

    fenwick = FenwickMax(N)
    dp = [0] * N
    ans = 0

    # using Binary indexed tree we solve this problem in nlogn
    for i in range(N):
        height = h[i]
        beauty = a[i]

        # Best dp value for any flower with smaller height
        best_prev = fenwick.query(height - 1)

        dp[i] = best_prev + beauty

        # Store this dp value at index = height
        fenwick.update(height, dp[i])

        ans = max(ans, dp[i])

    print(ans)


if __name__ == "__main__":
    solve()


# this is classoc O(n^2) way to solve the problem but it is not efficent for the contraints
def solve():
    N = int(input())
    h = list(map(int, input().split()))
    a = list(map(int, input().split()))

    dp = [0] * N
    ans = 0

    for i in range(N):
        dp[i] = a[i]   # start with just this flower
        for j in range(i):
            if h[j] < h[i]:
                dp[i] = max(dp[i], dp[j] + a[i])
        ans = max(ans, dp[i])

    print(ans)
