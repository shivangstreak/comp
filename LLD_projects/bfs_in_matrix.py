from collections import deque

# Define directions
directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]


def is_valid(matrix, visited, row, col):
    m, n = len(matrix), len(matrix[0])
    return 0 <= row < m and 0 <= col < n and not visited[row][col] and matrix[row][col] == 1


def bfs(matrix):
    m, n = len(matrix), len(matrix[0])
    visited = [[False] * n for _ in range(m)]

    queue = deque()
    queue.append((0, 0))
    visited[0][0] = True

    while queue:
        x, y = queue.popleft()

        if x == m - 1 and y == n - 1:  # If we reached destination
            return True

        for direction in directions:
            new_x, new_y = x + direction[0], y + direction[1]

            if is_valid(matrix, visited, new_x, new_y):
                queue.append((new_x, new_y))
                visited[new_x][new_y] = True

    return False


# Test our function
matrix = [
    [1, 0, 1, 1],
    [1, 1, 1, 0],
    [0, 0, 0, 1],
    [1, 1, 1, 1]
]

print(bfs(matrix))  # Should print True
