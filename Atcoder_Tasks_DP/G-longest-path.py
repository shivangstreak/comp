# Topological Sort + dp
from collections import defaultdict
from collections import deque
if __name__ == '__main__':
    n, m = map(int, input().split())
    adj = defaultdict(list)
    in_degree = [0] * (n+1)
    for i in range(m):
        x,y = map(int, input().split())
        adj[x].append(y) # edge from x -> y
        in_degree[y]+=1

    # Topological Sort (Kahn's Algorithm) O(n+m) algo
    q = deque()
    for v in range(1, n+1):
        if in_degree[v]==0:
            q.append(v)
    topo = []
    while q:
        u = q.popleft()
        topo.append(u)
        for v in adj[u]:
            in_degree[v]-=1
            if in_degree[v]==0:
                q.append(v)

    ans =0
    dp = [0] * (n+1)
    for u in topo:
        for v in adj[u]:
            if dp[v] < dp[u] + 1:
                dp[v] = dp[u] + 1
                ans = max(ans, dp[v])

    print(ans)