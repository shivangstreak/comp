from collections import defaultdict
if __name__ == '__main__':
    n = int(input())
    adj = defaultdict(list)
    for _ in range(n-1):
        u,v = map(int, input().split())
        adj[u].append(v)
        adj[v].append(u)
    # dp0[v] = number of ways subtree v can be painted if v is white
    # dp1[v] = number of ways subtree v can be painted if v is black
    dp0 = [0] * (n+1)
    dp1 = [0] * (n+1)
    MOD = 10**9 + 7
    def dfs(u , parent):
        dp0[u] = 1
        dp1[u] = 1
        for v in adj[u]:
            if v == parent:
                continue
            dfs(v, u)
            dp0[u] = dp0[u] * (dp1[v] + dp0[v]) %MOD
            dp1[u] = dp1[u] * dp0[v] %MOD
    dfs(1,-1)
    ans = (dp0[1] + dp1[1])%MOD
    print(ans)