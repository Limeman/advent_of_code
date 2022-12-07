import sys
import numpy as np

def read_positions():
    positions = []
    for line in sys.stdin:
        positions.append([[int(y) for y in x.split(",")] for x in line.strip().split("->")])
    return np.array(positions)

def get_map_size(positions):
    return (np.max(positions[:, :, 0]) + 1, np.max(positions[:, :, 1]) + 1)

def draw_vert(_map, x, ys):
    [y1, y2] = ys
    if y1 < y2:
        _map[x, y1:y2 + 1] += 1
    else:
        _map[x, y2:y1 + 1] += 1
    return _map

def draw_hor(_map, xs, y):
    [x1, x2] = xs
    if x1 < x2:
        _map[x1:x2 + 1, y] += 1
    else:
        _map[x2:x1 + 1, y] += 1
    return _map      

def main():
    positions = read_positions()
    map_size = get_map_size(positions)
    _map = np.zeros(map_size, dtype=int)
    
    for p in positions:
        [[x1, y1], [x2, y2]] = p
        if x1 == x2:
            _map = draw_vert(_map, x1, [y1, y2])
        if y1 == y2:
            _map = draw_hor(_map, [x1, x2], y1)
        
    print("Number of overlaps:\t" + str(np.count_nonzero(_map >= 2)))

if __name__ == "__main__":
    main()