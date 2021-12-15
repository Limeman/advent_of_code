import sys
import numpy as np
from numpy.core.numeric import isclose

def read_cave():
    adjacency = {}
    for line in sys.stdin:
        [x, y] = [x for x in line.split("-")]
        y = "".join([s for s in y if s != '\n'])
        if x in adjacency.keys():
            adjacency[x].append(y)
        else:
            adjacency[x] = [y]
        if y in adjacency.keys():
            adjacency[y].append(x)
        else:
            adjacency[y] = [x]
    adjacency_matrix = np.zeros((len(adjacency), len(adjacency)), dtype=int)
    mapping = {key:i for i, (key, _) in enumerate(adjacency.items())}
    for c, i in mapping.items():
        tmp = np.array([mapping[z] for z in adjacency[c]])
        adjacency_matrix[i, tmp] = 1
        adjacency_matrix[tmp, i] = 1
    return {value:key for (key, value) in mapping.items()}, adjacency_matrix

def get_neighbors(adjacency, node):
    return np.nonzero(adjacency[node, :] == 1)[0]


class path_counter:
    def __init__(self):
        self.count = 0
    
    def count_paths(self, adjacency, mapping, path):
        neighbors = get_neighbors(adjacency, path[-1])
        for i in range(neighbors.shape[0]):
            if mapping[neighbors[i]].isupper() or neighbors[i] not in path:
                if mapping[neighbors[i]] == 'end':
                    self.count += 1
                else:
                    self.count_paths(adjacency, mapping, path + [neighbors[i]])

def main():
    mapping, adjacency = read_cave()
    start_pos = list(mapping.keys())[list(mapping.values()).index('start')]
    counter = path_counter()
    counter.count_paths(adjacency, mapping, [start_pos])
    print(counter.count)

if __name__ == "__main__":
    main()