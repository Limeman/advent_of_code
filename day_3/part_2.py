import sys
import numpy as np

def get_most_common_number_in_row(bits):
    one_count = np.count_nonzero(bits == 1)
    zero_count = np.count_nonzero(bits == 0)
    if one_count >= zero_count:
        return 1
    else:
        return 0
def get_most_common_number_in_row_with_pos(bits, pos):
    one_count = np.count_nonzero(bits[:, pos] == 1)
    zero_count = np.count_nonzero(bits[:, pos] == 0)
    if one_count >= zero_count:
        return 1
    else:
        return 0

def get_least_common_number_in_row(bits, pos):
    one_count = np.count_nonzero(bits[:, pos] == 1)
    zero_count = np.count_nonzero(bits[:, pos] == 0)
    if zero_count <= one_count:
        return 0
    else:
        return 1

def get_oxygen_generator_rating(bits):
    print(bits.shape)
    for i in range(bits.shape[1]):
        if i == 0:
            most_common = get_most_common_number_in_row_with_pos(bits, i)
            curr_bits = np.nonzero(bits[:, i] == most_common)
        else:
            most_common = get_most_common_number_in_row(curr_bits)
            vert_bits = bits[:, i]
            curr_bits = np.nonzero(vert_bits[curr_bits] == most_common)
        print(curr_bits)
    return curr_bits


           
        

def main():
    values = []
    for line in sys.stdin:
        listified_line = [int(x) for x in line if x != "\n"]
        values.append(listified_line)
    bits = np.array(values)
    print(get_oxygen_generator_rating(bits))

if __name__ == "__main__":
    main()