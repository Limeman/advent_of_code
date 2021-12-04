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

def get_winner_axis(markers):
    x_sum = markers.sum(axis=1)
    y_sum = markers.sum(axis=2)

    if np.any(x_sum == 5):
        return 1
    elif np.any(y_sum == 5):
        return 2
    else:
        return -1

def get_winner_pos(markers, axis):
    return np.nonzero(markers.sum(axis=axis) == 5)

def get_winner_sum(board, markers):
    return board[markers == 0].sum()

def main():

    numbers = get_numbers()
    boards = get_boards()
    markers = np.zeros(boards.shape)
    winning_num = 0
    for n in numbers:
        matches = np.nonzero(boards == n)
        markers[matches] = 1

        if get_winner_axis(markers) != -1:
            winning_num = n
            break
    axis = get_winner_axis(markers)
    pos = get_winner_pos(markers, axis)
    winning_board = boards[pos[0], :, :]
    
    print("Final score:\t" + str(get_winner_sum(winning_board, markers[pos[0], :, :]) * n))

if __name__ == "__main__":
    main()