import sys

sys.setrecursionlimit(300000)

def solve():
    import sys
    input = sys.stdin.read
    data = input().split()

    N = int(data[0])
    MOD = int(data[1])

    # Build the tree
    graph = [[] for _ in range(N)]
    idx = 2
    for _ in range(N - 1):
        u = int(data[idx]) - 1
        v = int(data[idx + 1]) - 1
        idx += 2
        graph[u].append(v)
        graph[v].append(u)

    # dp[u] = number of valid colorings for subtree rooted at u where u is black
    dp = [0] * N
    ans = [0] * N

    # First DFS: compute dp values with arbitrary root (0)
    def dfs1(u, parent):
        res = 1  # Only u itself colored black
        for v in graph[u]:
            if v == parent:
                continue
            dfs1(v, u)
            res = (res * (dp[v] + 1)) % MOD
        dp[u] = res

    # Second DFS: rerooting - compute answer for each node as root
    def dfs2(u, parent, parent_contribution):
        # parent_contribution = contribution from parent's side when u is root

        # Get all children and their dp values
        children = []
        for v in graph[u]:
            if v != parent:
                children.append(v)

        # Precompute prefix and suffix products for efficient calculation
        prefix = [1] * (len(children) + 2)
        suffix = [1] * (len(children) + 2)

        # Fill prefix: prefix[i] = product of (dp[children[0]] + 1) * ... * (dp[children[i-1]] + 1)
        for i in range(len(children)):
            prefix[i + 1] = (prefix[i] * (dp[children[i]] + 1)) % MOD

        # Fill suffix: suffix[i] = product of (dp[children[i]] + 1) * ... * (dp[children[len(children)-1]] + 1)
        for i in range(len(children) - 1, -1, -1):
            suffix[i + 1] = (suffix[i + 2] * (dp[children[i]] + 1)) % MOD

        # Answer for current node as root
        # It's the product of all (dp[child] + 1) multiplied by (parent_contribution + 1)
        if parent == -1:
            # u is root, no parent contribution
            ans[u] = prefix[len(children)]
        else:
            ans[u] = (prefix[len(children)] * (parent_contribution + 1)) % MOD

        # Now compute contributions for each child
        for i, v in enumerate(children):
            # Contribution from u to v = product of:
            # 1. prefix[i] (children before v)
            # 2. suffix[i+2] (children after v)
            # 3. (parent_contribution + 1) (from u's parent)
            child_contribution = (prefix[i] * suffix[i + 2]) % MOD
            if parent != -1:
                child_contribution = (child_contribution * (parent_contribution + 1)) % MOD

            dfs2(v, u, child_contribution)

    # Execute the DFS calls
    dfs1(0, -1)
    dfs2(0, -1, 0)

    # Print results
    print("\n".join(map(str, ans)))


if __name__ == "__main__":
    solve()