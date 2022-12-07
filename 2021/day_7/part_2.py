import sys
import numpy as np

def get_crabs():
    return np.array([int(x) for x in sys.stdin.readline().split(",")], dtype=np.longlong)

def get_costs(crabs):
    furthest_crab = crabs.max()
    closest_crab = crabs.min()

    tmp = np.expand_dims(np.arange(closest_crab, furthest_crab + 1, dtype=np.longlong), axis=0)
    dists = np.repeat(tmp, crabs.shape[0], axis=0)
    
    crab_mat = np.repeat(np.expand_dims(crabs, axis=1), furthest_crab + 1, axis=1)

    return (np.abs(dists - crab_mat) * (np.abs(dists - crab_mat) + 1)) / 2

def main():
    crabs = get_crabs()
    costs = get_costs(crabs)

    print("Lowest fuel cost:\t" + str(np.min(costs.sum(axis=0))))


if __name__ == "__main__":
    main()