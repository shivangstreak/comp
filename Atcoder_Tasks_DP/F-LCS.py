def solve(s, t):
    n = len(s)
    m = len(t)
    # dp[i][j] = length of LCS of s[:i] and t[:j]
    dp = [[0] * (m+1) for _ in range(n+1)]
    for i in range(1, n+1):
        for j in range(1, m+1):
            if s[i-1]==t[j-1]:
                dp[i][j] = dp[i-1][j-1]+1
            else:
                dp[i][j] = max(dp[i-1][j], dp[i][j-1])
    # reconstruct LCS tracing back
    i,j = n, m
    lcs_chars = []
    while i>0 and j>0:
        if s[i-1]==t[j-1]:
            lcs_chars.append(s[i-1])
            i-=1
            j-=1
        else:
            # move in the direction of the larger dp value
            if dp[i-1][j]>=dp[i][j-1]:
                i-=1
            else:
                j-=1
    lcs_chars.reverse()
    return "".join(lcs_chars)

if __name__ == "__main__":
    #s,t = map(str, input().split())
    s = input().strip()
    t = input().strip()
    print(solve(s, t))