import sys
import numpy as np

def read_risk_map():
    risk_map = []
    for line in sys.stdin:
        risk_map.append([int(x) for x in line if x != '\n'])
    return np.array(risk_map, dtype=int)

def get_neighbors(pos, vertex_set, shape):
    tmp_neighbors = []
    if pos[0] + 1 < shape[0]:
        tmp_neighbors.append([pos[0] + 1, pos[1]])
    if pos[0] - 1 >= 0:
        tmp_neighbors.append([pos[0] - 1, pos[1]])
    if pos[1] + 1 < shape[1]:
        tmp_neighbors.append([pos[0], pos[1] + 1])
    if pos[1] - 1 >= 0:
        tmp_neighbors.append([pos[0], pos[1] - 1])
    
    neighbors = []
    for t in tmp_neighbors:
        if np.any(np.array(t) == vertex_set):
            neighbors.append(t)
    return np.array(neighbors, dtype=int)

def get_min(dist, vertex_set, verticies):
    mins = np.argsort(dist)
    for i in range(mins.shape[0]):
        if np.any((verticies[mins[i]][0] == vertex_set[:, 0]) & (verticies[mins[i]][1] == vertex_set[:, 1])):
            return mins[i]

def shortest_path(risk_map):
    shape = risk_map.shape
    vertex_set = np.reshape(np.indices(shape), (2, shape[0] * shape[1])).T
    verticies  = np.reshape(np.indices(shape), (2, shape[0] * shape[1])).T
    dist       = np.full((shape[0] * shape[1],), np.iinfo(int).max, dtype=int)
    prev       = np.full((shape[0] * shape[1],), np.nan, dtype=int)
    dist[0] = 0
    
    count = 0
    while vertex_set.shape[0] != 0:
        u = get_min(dist, vertex_set, verticies)
        pos = verticies[u, :]
        vertex_set = vertex_set[~(pos[0] == vertex_set[:, 0]) & (pos[1] == vertex_set[:, 1])]

        neighbors = get_neighbors(verticies[u], vertex_set, shape)
        for i in range(neighbors.shape[0]):
            tentative = dist[u] + risk_map[neighbors[i][0], neighbors[i][1]]
            loc = (verticies[:, 0] == neighbors[i, 0]) & (verticies[:, 1] == neighbors[i, 1])
            if tentative < dist[loc]:
                dist[loc] = tentative
                prev[loc] = u
        count += 1
    return dist, prev


def main():
    risk_map = read_risk_map()
    print(shortest_path(risk_map))

if __name__ == "__main__":
    main()