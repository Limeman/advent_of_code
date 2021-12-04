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
    x_boards = np.nonzero(markers.sum(axis=1) == 5)[0]
    y_boards = np.nonzero(markers.sum(axis=2) == 5)[0]
    return np.unique(np.concatenate((x_boards, y_boards)))    

def get_final_sum(board, markers):
    return board[markers == 0].sum()

def main():

    numbers = get_numbers()
    boards = get_boards()
    
    markers = np.zeros(boards.shape)
    num_boards = boards.shape[0]
    non_bingos = np.ones((num_boards, ), dtype=bool)
    
    last_board = -1
    last_number = 0
    
    for n in numbers:
        markers[boards == n] = 1
        bingo_cards = get_bingo_boards(markers)
        non_bingos[bingo_cards] = 0
        
        if non_bingos.sum() == 1:
            last_board = np.nonzero(non_bingos == 1)
        if non_bingos.sum() == 0:
            last_number = n
            break

    print("Losing boards score:\n" + str(get_final_sum(boards[last_board, :, :], markers[last_board, :, :]) * last_number))
    

if __name__ == "__main__":
    main()