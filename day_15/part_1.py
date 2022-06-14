import sys
import numpy as np
from sklearn import neighbors
from torch import ne

def read_risk_map():
    risk_map = []
    for line in sys.stdin:
        risk_map.append([int(x) for x in line if x != '\n'])
    return np.array(risk_map, dtype=int)

def extract_min(queue):
    return np.unravel_index(np.nanargmin(queue), queue.shape)

def get_neighbors(pos, bounds):
    (x, y) = pos
    (x_max, y_max) = bounds
    neighbors = []
    for i in range(-1, 2):
        for j in range(-1, 2):
            if x + i >= 0 and x + i < x_max and\
               y + j >= 0 and y + j < y_max and\
               i != j and (i, j) != (1, -1) and (i, j) != (-1, 1):
               neighbors.append((x + i, y + j))
    return neighbors
                

def dijkstra(risk_map, source):
    (x, y) = source
    dist  = np.full(risk_map.shape, np.inf)
    queue = np.full(risk_map.shape, np.inf)
    prev  = np.full(risk_map.shape + (2,), -1)
    
    dist[x, y]  = 0
    queue[x, y] = dist[x, y]

    while np.isnan(queue).all() == False:
        (x, y) = extract_min(queue)
        queue[x, y] = np.nan
        for n in get_neighbors((x, y), risk_map.shape):
            (xn, yn) = n
            tentative = dist[x, y] + risk_map[xn, yn]
            if tentative < dist[xn, yn] and queue[xn, yn] != np.nan:
                dist[xn, yn] = tentative
                prev[xn, yn, 0] = x
                prev[xn, yn, 1] = y
                queue[xn, yn] = tentative
    return dist, prev



def main():
    risk_map = read_risk_map()
    dist, prev = dijkstra(risk_map, (0, 0))
    print(dist)
    print(risk_map)
    print(int(dist[-1, -1]))

if __name__ == "__main__":
    main()