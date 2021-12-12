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
    return adjacency[node, :]

def dfs(adjacency, mapping, stack, visited):
    if len(stack) == 0:
        return 0
    curr = stack.pop()
    if mapping[curr] == 'end':
        return 1
    if mapping[curr].islower() and mapping[curr] != 'start' and mapping[curr] != 'end':
        visited[curr] = True
    
    neighbors = get_neighbors(adjacency, curr)
    for n in neighbors:
        if visited[n] == False:
            if n.islower() and n != 'end':
                visited[n] = True
            stack.append(n)
    return dfs(adjacency, mapping, stack, visited)
def main():
    mapping, adjacency = read_cave()
    
    print(dfs(adjacency, mapping, [], np.zeros((len(mapping),), dtype=bool)))

if __name__ == "__main__":
    main()