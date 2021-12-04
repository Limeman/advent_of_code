import sys
import numpy as np

def get_numbers():
    str_numbers = sys.stdin.readline()
    return [int(x) for x in str_numbers.split(",")]

def get_boards():
    boards = []
    for line_num, line in enumerate(sys.stdin):
        if line_num == 0:
            curr_board = []
        elif line == "\n":
            boards.append(curr_board)
            curr_board = []
        else:
            row = np.array([int(x) for x in line.strip().split(" ") if x != ""])
            curr_board.append(row)
    # Last board does not have a newline after it
    boards.append(curr_board)

    return np.array(boards)

def get_bingo_boards(markers):
    print(np.nonzero(markers.sum(axis=1) == 5)[0])
    np.nonzero(markers.sum(axis=2) == 5)[0]

def get_final_sum(board, markers):
    return board[markers == 0].sum()

def main():

    numbers = get_numbers()
    boards = get_boards()
    num_boards = boards.shape[0]
    markers = np.zeros(boards.shape)
    losing_num = 0
    for n in numbers:
        markers[boards == n] = 1

        get_bingo_boards(markers)


    

if __name__ == "__main__":
    main()