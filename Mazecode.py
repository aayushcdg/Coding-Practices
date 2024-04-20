
import copy

def loadMaze(mazeStr, rows, cols):
    # Split the input maze string by newline and remove the first and last empty rows
    maze_rows = mazeStr.split('\n')[1:-1]

    maze = []
    for row in maze_rows:
        # Remove the left and right border walls to create the maze matrix
        maze.append(list(row[1:-1]))

    return maze

def solveMaze(maze):
    rows = len(maze)
    cols = len(maze[0])

    def is_valid_move(row, col):
        # Check if a move to (row, col) is within the maze boundaries and the cell is empty (' ')
        return 0 <= row < rows and 0 <= col < cols and maze[row][col] == ' '

    stack = [copy.deepcopy([[1, 0], 0])]  # Start at (1, 0) with a path length of 0
    maze[1][0] = 'X'  # Mark the starting point as visited

    while stack:
        current_row, current_col = stack[-1][0]
        path_length = stack[-1][1]

        if current_row == rows - 2 and current_col == cols - 2:
            break  # Found the '#' symbol, exit the loop

        move_down = is_valid_move(current_row + 1, current_col)
        move_right = is_valid_move(current_row, current_col + 1)

        if move_down and move_right:
            # Can move in both directions, prioritize moving down
            stack.append(copy.deepcopy([[current_row + 1, current_col], path_length + 1]))
            maze[current_row + 1][current_col] = 'X'  # Mark the path
        elif move_down:
            stack.append(copy.deepcopy([[current_row + 1, current_col], path_length + 1]))
            maze[current_row + 1][current_col] = 'X'  # Mark the path
        elif move_right:
            stack.append(copy.deepcopy([[current_row, current_col + 1], path_length + 1]))
            maze[current_row][current_col + 1] = 'X'  # Mark the path
        else:
            stack.pop()  # Backtrack

    # Convert the path into 'S' and 'E'
    path = ''
    for i in range(1, len(stack)):
        prev_row, prev_col = stack[i - 1][0]
        current_row, current_col = stack[i][0]

        if current_row > prev_row:
            path += 'S'
        else:
            path += 'E'

    maze_dimensions = f"maze dimensions: {cols - 2}x{rows - 2}"
    found_coords = f"found # at coords: {current_row},{current_col}"
    total_searches = len(stack)
    total_valid_locations = (rows - 2) * (cols - 2)
    percentage_searched = f"{total_searches}/{total_valid_locations} {100 * total_searches / total_valid_locations:.4f}% of maze"

    # Display the maze, excluding the 'X's at the start
    maze_str = ""
    for i in range(1, rows - 1):
        maze_str += "".join([cell if cell != 'X' else ' ' for cell in maze[i][1:-1]]) + "\n"

    print(maze_str)
    print(maze_dimensions)
    print(found_coords)
    print(f"path: {path}")
    print(total_searches)
    print(percentage_searched)
