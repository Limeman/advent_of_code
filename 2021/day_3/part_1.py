import sys
import numpy as np

def get_gamma(bits):
    gamma = ""
    for i in range(12):
        zero_count = np.count_nonzero(bits[:, i] == 0)
        one_count = np.count_nonzero(bits[:, i] == 1)
        if zero_count > one_count:
            gamma += "0"
        else:
            gamma += "1"
    return gamma

def get_epsilon(bits):
    epsilon = ""
    for i in range(12):
        zero_count = np.count_nonzero(bits[:, i] == 0)
        one_count = np.count_nonzero(bits[:, i] == 1)
        if zero_count > one_count:
            epsilon += "1"
        else:
            epsilon += "0"
    return epsilon

def main():
    bits = np.zeros((1000, 12))

    x_count = 0
    y_count = 0
    for line in sys.stdin:
        for l in line:
            if l == "\n":
                continue
            bits[y_count, x_count] = int(l)
            x_count += 1
        x_count = 0
        y_count += 1
    
    print("Power Consumption:\t" + str(int(get_epsilon(bits), 2) * int(get_gamma(bits), 2)))



if __name__ == "__main__":
    main()