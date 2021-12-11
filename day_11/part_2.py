import sys
import numpy as np
from collections import deque

from numpy.core.numeric import count_nonzero

def get_octopi():
    octopi = []
    for line in sys.stdin:
        octopi.append([int(x) for x in line if x != "\n"])
    return np.array(octopi)

def contains_flash(octopi):
    return np.any(octopi > 9)

def increment_neighbors(octopi, pos):
    (x, y) = pos
    # There probably is a smarter way to do this but I'm tired and its late
    if x + 1 < octopi.shape[0]:
        octopi[x + 1, y] += 1
    if x - 1  >= 0:
        octopi[x - 1, y] += 1
    if y + 1 < octopi.shape[1]:
        octopi[x, y + 1] += 1
    if y - 1 >= 0:
        octopi[x, y - 1] += 1
    if x - 1 >= 0 and y - 1 >= 0:
        octopi[x - 1, y - 1] += 1
    if x + 1 < octopi.shape[0] and y + 1 < octopi.shape[1]:
        octopi[x + 1, y + 1] += 1
    if x + 1 < octopi.shape[0] and y - 1 >= 0:
        octopi[x + 1, y - 1] += 1
    if x - 1 >= 0 and y + 1 < octopi.shape[1]:
        octopi[x - 1, y + 1] += 1
    return octopi

def main():
    octopi = get_octopi()
    flashes = 0
    count = 1
    all_flash_time = 0
    while True:
        octopi += 1
        flashed = np.zeros(octopi.shape, dtype=bool)
        while np.any(np.bitwise_and(octopi > 9, flashed == False)):
            xs, ys = np.nonzero(np.bitwise_and(octopi > 9, flashed == False))
            flashes += xs.shape[0]
            for j in range(xs.shape[0]):
                octopi = increment_neighbors(octopi, (xs[j], ys[j]))
            flashed[xs, ys] = True
        octopi[flashed] = 0
        if np.all(octopi == 0):
            all_flash_time = count
            break
        count += 1
    print(all_flash_time)




if __name__ == "__main__":
    main()