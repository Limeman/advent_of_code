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
    # Last board does not have a newline
    boards.append(curr_board)

    return np.array(boards)


def main():

    numbers = get_numbers()
    boards = get_boards()
    markers = np.zeros(boards.shape())

    for n in numbers:
        


if __name__ == "__main__":
    main()