import sys
import numpy as np
from collections import deque

from numpy.core.fromnumeric import sort


def get_heightmap():
    heightmap = []
    for line in sys.stdin:
        heights = [int(x) for x in line if x != '\n']
        heightmap.append(heights)
    return np.array(heightmap, dtype=int)

def get_neighbors(heightmap, pos):
    neighbors = []
    (x, y) = pos
    if x + 1 < heightmap.shape[0] and heightmap[x + 1, y] != 9:
        neighbors.append((x + 1, y))
    if x - 1 >= 0 and heightmap[x - 1, y] != 9:
        neighbors.append((x - 1, y))
    if y + 1 < heightmap.shape[1] and heightmap[x, y + 1] != 9:
        neighbors.append((x, y + 1))
    if y - 1 >= 0 and heightmap[x, y - 1] != 9:
        neighbors.append((x, y - 1))
    return neighbors

def get_basin_size(heightmap, q, visited):
    if not q:
        return 0
    pos = q.popleft()
    neighbors = get_neighbors(heightmap, pos)
    for n in neighbors:
        (x, y) = n
        if visited[x, y] == False:
            visited[x, y] = True
            q.append((x, y))
    return 1 + get_basin_size(heightmap, q, visited)


def main():
    heightmap = get_heightmap()
    windows = np.lib.stride_tricks.sliding_window_view(np.pad(heightmap, (1, 1), constant_values=(9, 9)), (3, 3))
    row_mask = np.array([0, 1, 1, 2])
    col_mask = np.array([1, 0, 2, 1])
    low_x, low_y = np.nonzero(np.min(windows[:, :, row_mask, col_mask], axis=2) > windows[:, :, 1, 1])
    
    basin_sizes = []
    for i in range(len(low_x)):
        pos = (low_x[i], low_y[i])
        q = deque()
        q.append(pos)
        visited = np.zeros(heightmap.shape, dtype=bool)
        visited[pos[0], pos[1]] = True
        basin_sizes.append(get_basin_size(heightmap, q, visited))
    
    three_largest = np.array(sorted(basin_sizes, reverse=True))[:3]
    print("Three basin combo:\t" + str(np.prod(three_largest)))


if __name__ == "__main__":
    main()