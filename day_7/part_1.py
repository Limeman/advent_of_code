import sys
import numpy as np

def get_crabs():
    return np.array([int(x) for x in sys.stdin.readline().split(",")])

def get_costs(crabs):
    furthest_crab = crabs.max()

    tmp = np.expand_dims(np.arange(furthest_crab + 1), axis=1)
    dists = np.repeat(tmp, crabs.shape[0], axis=1)

    crab_mat = np.repeat(np.expand_dims(crabs, axis=0), furthest_crab + 1, axis=0)

    print(dists)
    print(crab_mat)
    return np.abs(dists - crab_mat)



def main():
    crabs = get_crabs()
    costs = get_costs(crabs)
    print(costs)
    print(costs.sum(axis=1))
    print(costs.shape)
    print("Cheapest movement:\t" + str(np.argmin(costs.sum(axis=1))))

if __name__ == "__main__":
    main()