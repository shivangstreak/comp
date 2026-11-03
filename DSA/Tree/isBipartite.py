from collections import deque
class Solution:
    def isBipartite(self, graph: list[list[int]]) -> bool:
        n = len(graph)
        color = [-1] * n # -1 not colored , 0 red , 1 blue
        for x in range(n):
            if color[x]!=-1:
                continue
            q = deque([x])
            color[x] = 0
            while q:
                u = q.popleft()
                for v in graph[u]:
                    if color[v]==-1:
                        color[v] = 1 - color[u]
                        q.append(v)
                    elif color[v]==color[u]:
                        return False
        return True