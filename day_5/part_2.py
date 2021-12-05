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

def draw_diag(_map, p):
    [[x1, y1], [x2, y2]] = p
    [x_diff, y_diff] = [x2 - x1, y2 - y1]
    x_incrementor = -1 if x_diff < 0 else 1
    y_incrementor = -1 if y_diff < 0 else 1

    [x, y] = [x1, y1]
    while True:
        _map[x, y] += 1
        if [x, y] == [x2, y2]:
            break
        x += x_incrementor
        y += y_incrementor

    return _map
        

def main():
    positions = read_positions()
    map_size = get_map_size(positions)
    _map = np.zeros(map_size, dtype=int)
    
    for p in positions:
        [[x1, y1], [x2, y2]] = p
        if x1 == x2:
            _map = draw_vert(_map, x1, [y1, y2])
        elif y1 == y2:
            _map = draw_hor(_map, [x1, x2], y1)
        else:
            _map = draw_diag(_map, p)
    print("Number of overlaps:\t" + str(np.count_nonzero(_map >= 2)))

if __name__ == "__main__":
    main()