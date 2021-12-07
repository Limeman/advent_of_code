import sys
import numpy as np

def get_crabs():
    return np.array([int(x) for x in sys.stdin.readline().split(",")], dtype=np.longlong)

def get_costs(crabs):
    furthest_crab = crabs.max()
    closest_crab = crabs.min()
    
    tmp = np.expand_dims(np.arange(closest_crab, furthest_crab + 1, dtype=np.longlong), axis=1)
    dists = np.repeat(tmp, crabs.shape[0], axis=1)

    crab_mat = np.repeat(np.expand_dims(crabs, axis=0), furthest_crab + 1, axis=0)

    print(crab_mat)
    print(dists)
    return np.abs(dists - crab_mat)



def main():
    crabs = get_crabs()
    costs = get_costs(crabs)
    print(costs.T)
    print(costs.sum(axis=1))
    print(np.argwhere(costs.sum(axis=1) <= 356179))
    print("Cheapest movement:\t" + str(np.argmin(costs.sum(axis=1))))


if __name__ == "__main__":
    main()