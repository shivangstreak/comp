def stories(endings, choices, option):
    # Create a dictionary to map from current page to the next page based on the option
    next_pages = {choice[0]: choice[option] for choice in choices}

    # Set of visited pages to detect loops
    visited = set()

    # Start from page 1
    page = 1
    while page not in endings:
        # If we've visited this page before, we're in a loop
        if page in visited:
            return -1
        # Mark this page as visited
        visited.add(page)
        # If this page has a choice, move to the next page based on the option, otherwise, just go to the next page
        page = next_pages.get(page, page + 1)

    return page



def find_good_endings(good_endings, bad_endings, choices):
    # Convert the endings to sets for faster lookup
    good_endings = set(good_endings)
    bad_endings = set(bad_endings)

    # Create a dictionary to map from current page to the next pages based on the choices
    next_pages = {choice[0]: choice[1:] for choice in choices}

    # Set of visited pages to avoid revisiting them
    visited = set()

    # Set of reachable good endings
    reachable_good_endings = set()

    # Define a recursive function to perform the DFS
    def dfs(page):
        if page in good_endings:
            reachable_good_endings.add(page)
        elif page not in bad_endings and page not in visited:
            visited.add(page)
            for next_page in next_pages.get(page, [page + 1]):
                dfs(next_page)

    # Start the DFS from page 1
    dfs(1)

    # Convert the set of reachable good endings to a sorted list and return it
    return sorted(list(reachable_good_endings))



def disappear(grid, row, col):
    # Calculate grid dimensions
    n, m = len(grid), len(grid[0])

    # Get the value of the selected tile
    tile_value = grid[row][col]

    # Create a set to keep track of visited tiles
    visited = set()

    # Define a helper function for the depth-first search
    def dfs(i, j):
        # Check if the tile is in the grid and has not been visited yet
        if 0 <= i < n and 0 <= j < m and (i, j) not in visited and grid[i][j] == tile_value:
            # Mark the tile as visited
            visited.add((i, j))

            # Continue the depth-first search in the four possible directions
            dfs(i + 1, j)
            dfs(i - 1, j)
            dfs(i, j + 1)
            dfs(i, j - 1)

    # Start the depth-first search from the selected tile
    dfs(row, col)

    # Return the number of tiles that will disappear
    return len(visited)
