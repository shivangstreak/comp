def destinations(teleporters, die, start, end):
    board = [False] * (end + 1)  # Create a board of squares, initially all False
    board[start] = True  # Mark the starting square as visited

    queue = [start]  # Initialize a queue with the starting square

    while queue:
        current_square = queue.pop(0)  # Get the next square from the queue
        for roll in range(1, die + 1):
            next_square = current_square + roll
            if next_square <= end:
                # Check if the next square has a teleporter
                teleporter = None
                for t in teleporters:
                    t_start, t_end = map(int, t.split(','))
                    if t_start == next_square:
                        teleporter = t_end
                        break

                # Determine the destination square
                if teleporter is not None:
                    next_square = teleporter

                # If the next square hasn't been visited, mark it and add it to the queue
                if not board[next_square]:
                    board[next_square] = True
                    queue.append(next_square)

    # Collect the squares that have been visited
    possible_squares = [square for square, visited in enumerate(board) if visited]
    return possible_squares
