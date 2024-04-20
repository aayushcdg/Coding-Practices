import copy

def loadMaze(mazeStr, r, c):
    maze = [[mazeStr[i * c + j] for j in range(c)] for i in range(r)]
    return maze

def solveMaze(maze):
    rows = len(maze)
    cols = len(maze[0])

    stack = []  # To store coordinates and path length
    path = ""
    visited = copy.deepcopy(maze)  # Create a mask to mark visited cells

    # Find the starting point
    start_row, start_col = 0, 0
    for i in range(rows):
        for j in range(cols):
            if maze[i][j] == "@":
                start_row, start_col = i, j
                break

    row, col = start_row, start_col

    while maze[row][col] != '#':
        visited[row][col] = 'X'  # Mark visited cells
        stack.append([row, col, len(path)])  # Store current position and path length
        right_move = row, col + 1  # Coordinates for moving right
        down_move = row + 1, col  # Coordinates for moving down

        if col + 1 < cols and visited[right_move[0]][right_move[1]] != 'X':
            col += 1  # Move right
            path += 'E'  # Update path
        elif row + 1 < rows and visited[down_move[0]][down_move[1]] != 'X':
            row += 1  # Move down
            path += 'S'  # Update path
        else:
            # Dead end, backtrack
            while stack[-1][0] != row or stack[-1][1] != col:
                stack.pop()  # Remove entries until reaching a junction
            row, col, path_len = stack.pop()  # Backtrack to the last junction
            path = path[:path_len]  # Remove unnecessary characters

    # Print maze dimensions, found coordinates, path, and search statistics
    print("maze dimensions:", cols, "x", rows)
    print("found # at coords:", row + 1, ",", col + 1)
    print("path:", path)
    total_searches = len(stack)
    total_valid_locations = rows * cols - total_searches
    percentage_searched = (total_searches / total_valid_locations) * 100
    print("total searches:", total_searches, "/", total_valid_locations, f"{percentage_searched:.4f}% of maze")

def main():
    maze1 = '''-------------------+
   @                  |
   | | --+ | | -------+
   | |   | | |      # |
   | +-+ | | +-+ | ---+
   |   | | |   | |    |
   | | | +-+ | +-+----+
   | | |   | |        |
   | | |   | |        |
   +-+-+---+-+--------+'''

    maze2 = '''-------------------------------+
   @                              |
   | --+ --+ --+ | --------+ | |  |
   |   |   |   | |         | | |  |
   | --+---+-+ | +-+ | | | +-+ |  |
   |         | |   | | | |   | |  |
   | ------+ | | | | | | | | +-+  |
   |       | | |#| | | | | |   |  |
   | ------+ +-+ | +-+-+-+ +-+ +--+
   |       |   | |       |   |    |
   | --+ --+ --+ +-----+ +-+ +-+  |
   |   |   |   |       |   |   |  |
   | --+ | | --+-+ | --+ | | | |  |
   |   | | |     | |   | | | | |  |
   | | +-+ | | | +-+ --+ | +-+ |  |
   | |   | | | |   |   | |   | |  |
   | | --+-+ +-+---+ --+-+ | +-+--+
   | |     |       |     | |      |
   | +---+ | ------+-+ --+ | --+  |
   |     | |         |   | |   |  |
   | ----+ +-+ | --+ +-+ | | --+--+
   |     |   | |   |   | | |      |
   +-----+---+-+---+---+-+-+------+'''

    maze3 = '''-------------------+
   @  #               |
   | --+ | | | ----+  |
   |   | | | |     |  |
   | --+ | +-+ | | |  |
   |   | |   | | | |  |
   | | +-+-+ | | | +--+
   | |     | | | |    |
   | |     | | | |    |
   +-+-----+-+-+-+----+'''

    maze4 = '''--------------------+
   @                   |
   | | ----------------+
   | |#                |
   | | | ----+ ----+ | |
   | | |     |     | | |
   | | +-----+---+ | +-+
   | |           | |   |
   | +-+ --+ | | +-+ --+
   |   |   | | |   |   |
   |   |   | | |   |   |
   +---+---+-+-+---+---+'''

    rows = [10, 23, 10, 12]
    cols = [20, 32, 20, 21]
    mazes = [maze1, maze2, maze3, maze4]
    for i in range(4):
        matrix = loadMaze(mazes[i], rows[i], cols[i])
        solveMaze(matrix)
        if i < 3:
            print()

if __name__ == "__main__":
    main()
