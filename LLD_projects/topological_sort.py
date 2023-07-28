# Kahn's algorithm is a popular method for performing topological sorting on a directed acyclic graph (DAG).
def topological_sort(graph):
    in_degree = {v: 0 for v in graph}
    for v in graph:
        for neighbor in graph[v]:
            in_degree[neighbor] += 1

    queue = []
    for v in in_degree:
        if in_degree[v] == 0:
            queue.append(v)

    sorted_result = []
    while queue:
        vertex = queue.pop(0)
        sorted_result.append(vertex)
        for neighbor in graph[vertex]:
            in_degree[neighbor] -= 1
            if in_degree[neighbor] == 0:
                queue.append(neighbor)

    if len(sorted_result) != len(graph):
        # Graph contains a cycle
        return None
    else:
        return sorted_result
