# https://atcoder.jp/contests/dp/tasks/dp_x

# Time complexity is O(N × W)

def solve():
    import sys
    input = sys.stdin.read
    data = input().split()

    N = int(data[0])
    blocks = []
    idx = 1
    for _ in range(N):
        w = int(data[idx])
        s = int(data[idx + 1])
        v = int(data[idx + 2])
        idx += 3
        blocks.append((w, s, v))

    # Sort blocks by (weight + strength)
    blocks.sort(key=lambda x: x[0] + x[1])

    max_weight = 30000
    # dp[i][j] = max value with first i blocks and total weight j
    dp = [[-10 ** 18] * (max_weight + 1) for _ in range(N + 1)]
    dp[0][0] = 0  # Base case: 0 blocks, 0 weight, 0 value

    for i in range(1, N + 1):
        w, s, v = blocks[i - 1]

        for j in range(max_weight + 1):
            # Option 1: Don't take the i-th block
            dp[i][j] = max(dp[i][j], dp[i - 1][j])

            # Option 2: Take the i-th block (if possible)
            if j >= w and dp[i - 1][j - w] != -10 ** 18:
                # Check if we can place this block (weight of blocks above <= s)
                # Weight of blocks above = total weight - current block's weight
                weight_above = j - w
                if weight_above <= s:
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - w] + v)

    answer = 0
    for j in range(max_weight + 1):
        answer = max(answer, dp[N][j])

    print(answer)


if __name__ == "__main__":
    solve()

#O(N × W) where W is the maximum weight we consider

#Efficient enough for the given constraints (N ≤ 1000, W ≤ 30000)
def solve():
    import sys
    input = sys.stdin.read
    data = input().split()

    N = int(data[0])
    blocks = []
    idx = 1
    for _ in range(N):
        w = int(data[idx])
        s = int(data[idx + 1])
        v = int(data[idx + 2])
        idx += 3
        blocks.append((w, s, v))

    # Sort blocks by (weight + strength)
    blocks.sort(key=lambda x: x[0] + x[1])

    # DP array: dp[i] = max value with total weight i
    max_weight = 30000  # Based on constraints: max s_i = 20000, reasonable upper bound
    dp = [0] * (max_weight + 1)

    for w, s, v in blocks:
        # Process from high to low to avoid reusing the same block
        for current_weight in range(s, -1, -1):
            new_weight = current_weight + w
            if new_weight <= max_weight:
                dp[new_weight] = max(dp[new_weight], dp[current_weight] + v)

    print(max(dp))


if __name__ == "__main__":
    solve()