import sys
import numpy as np
from numpy.core.fromnumeric import shape

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

def get_least_common_numer_in_row(bits):
    one_count = np.count_nonzero(bits == 1)
    zero_count = np.count_nonzero(bits == 0)
    if zero_count <= one_count:
        return 0
    else:
        return 1
def get_least_common_number_in_row_with_pos(bits, pos):
    one_count = np.count_nonzero(bits[:, pos] == 1)
    zero_count = np.count_nonzero(bits[:, pos] == 0)
    if zero_count <= one_count:
        return 0
    else:
        return 1

def get_oxygen_generator_rating(bits):
    for i in range(bits.shape[1]):
        if i == 0:
            most_common = get_most_common_number_in_row_with_pos(bits, i)
            curr_bits = np.nonzero(bits[:, i] == most_common)
            continue
        else:
            vert_bits = bits[:, i]
            most_common = get_most_common_number_in_row(vert_bits[curr_bits])
            matches = np.nonzero(vert_bits == most_common)
            curr_bits = np.array(np.intersect1d(curr_bits, matches))
        
        if len(curr_bits) == 1:
            break
    return binary_to_int(bits[curr_bits[0], :])

def get_co2_scrubber_rating(bits):
    for i in range(bits.shape[1]):
        if i == 0:
            least_common = get_least_common_number_in_row_with_pos(bits, i)
            curr_bits = np.nonzero(bits[:, i] == least_common)
            continue
        else:
            vert_bits = bits[:, i]
            least_common = get_least_common_numer_in_row(vert_bits[curr_bits])
            matches = np.nonzero(vert_bits == least_common)
            curr_bits = np.array(np.intersect1d(curr_bits, matches))
        if len(curr_bits) == 1:
            break
    return binary_to_int(bits[curr_bits[0], :])

def binary_to_int(binary_array):
    return binary_array.dot(2**np.arange(binary_array.size)[::-1])
           
        

def main():
    values = []
    for line in sys.stdin:
        listified_line = [int(x) for x in line if x != "\n"]
        values.append(listified_line)
    bits = np.array(values)
    oxygen_generator_rating = get_oxygen_generator_rating(bits)
    co2_generator_rating = get_co2_scrubber_rating(bits)
    print("Life support rating:\t" + str(oxygen_generator_rating * co2_generator_rating))

if __name__ == "__main__":
    main()