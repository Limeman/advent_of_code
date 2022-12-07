import sys
import numpy as np

def get_fish():
    fish = np.array([int(x) for x in sys.stdin.readline().split(",")])
    ret_val = np.zeros((9,), dtype=int)
    for i in range(9):
        ret_val[i] = np.count_nonzero(fish == i)
    return ret_val


def main():
    fish = get_fish()
    for i in range(80):
        reproducing_fish = fish[0]
        # | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
        # | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
        fish[0:8] = fish[1:9]
        # | 0 |
        # | 6 |
        fish[6] += reproducing_fish
        # | 0 |
        # | 8 |
        fish[8] = reproducing_fish
    
    print("Total number of fish:\t" + str(fish.sum()))

if __name__ == "__main__":
    main()