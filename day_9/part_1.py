import sys
import numpy as np

def get_heightmap():
    heightmap = []
    for line in sys.stdin:
        heights = [int(x) for x in line if x != '\n']
        heightmap.append(heights)
    return np.array(heightmap, dtype=int)

def get_nth_smallest(a, n):
    a = a.flatten()
    return np.partition(a, n)[n]


def main():
    heightmap = get_heightmap()
    windows = np.lib.stride_tricks.sliding_window_view(np.pad(heightmap, (1, 1), constant_values=(9, 9)), (3, 3))
    print(windows.shape)
    row_mask = np.array([True, False, True])
    col_mask = np.array([True, False, True])
    print(windows[:, :, row_mask, col_mask])
    print(windows[:, :, row_mask, col_mask].shape)
    low_x, low_y = np.nonzero(np.min(windows[:, :, row_mask, col_mask], axis=(2, 3)) == windows[:, :, 1, 1])
    print("Sum of low points:\t" + str(np.sum(heightmap[low_x, low_y] + 1)))

if __name__ == "__main__":
    main()