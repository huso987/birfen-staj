# Write a program to solve a Sudoku puzzle by filling the empty cells.

# A sudoku solution must satisfy all of the following rules:

# Each of the digits 1-9 must occur exactly once in each row.
# Each of the digits 1-9 must occur exactly once in each column.
# Each of the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.
# The '.' character indicates empty cells.

def is_valid(board, row, col, digit):
    for i in range(9):
        if board[row][i] == digit:
            return False
    for i in range(9):
        if board[i][col] == digit:
            return False

    start_row = (row // 3) * 3
    start_col = (col // 3) * 3
    for i in range(3):
        for j in range(3):
            if board[start_row + i][start_col + j] == digit:
                return False
    return True
    
def solve_sudoku(board):
    for i in range(9):
        for j in range(9):
            if board[i][j] == '.':
                # Try digits from 1 to 9
                for digit in '123456789':
                    if is_valid(board, i, j, digit):
                        board[i][j] = digit
                        if solve_sudoku(board):
                            return True
                        board[i][j] = '.'
                return False
    return True
def solveSudoku(board):
    solve_sudoku(board)

# örnek puzzle
board = [
    ['5', '3', '.', '.', '7', '.', '.', '.', '.'],
    ['6', '.', '.', '1', '9', '5', '.', '.', '.'],
    ['.', '9', '8', '.', '.', '.', '.', '6', '.'],
    ['8', '.', '.', '.', '6', '.', '.', '.', '3'],
    ['4', '.', '.', '8', '.', '3', '.', '.', '1'],
    ['7', '.', '.', '.', '2', '.', '.', '.', '6'],
    ['.', '6', '.', '.', '.', '.', '2', '8', '.'],
    ['.', '.', '.', '4', '1', '9', '.', '.', '5'],
    ['.', '.', '.', '.', '8', '.', '.', '7', '9']
]

solveSudoku(board)

for row in board:
    print(row)
