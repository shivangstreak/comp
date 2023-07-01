# uses dfs to search for a word in a matrix.
def search(grid, word):
    rows, cols = len(grid), len(grid[0])
    directions = [(0, 1), (1, 0)]  # right, down

    def dfs(i, j, idx, path):
        # Base case - if we've used up all the characters in the word
        if idx == len(word):
            return path

        # If we're out of bounds or the current letter doesn't match the word's letter
        if i < 0 or i >= rows or j < 0 or j >= cols or grid[i][j] != word[idx]:
            return None

        # Continue the DFS in all possible directions
        for di, dj in directions:
            result = dfs(i + di, j + dj, idx + 1, path + [(i, j)])
            if result:
                return result

        return None

    for i in range(rows):
        for j in range(cols):
            path = dfs(i, j, 0, [])
            if path:
                return path

    return None