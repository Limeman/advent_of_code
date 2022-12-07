import argparse
from struct import pack
import sys
from matplotlib.pyplot import axis
import numpy as np
import getopt


def zero_pad(a):
    n = a.size
    m = np.zeros((8-n,), dtype=bool)
    return np.concatenate((m, a), axis=0)

def get_version(package):
    return np.packbits(zero_pad(package[:3]))

def get_type_id(package):
    return np.packbits(zero_pad(package[3:6]))

def get_length_type_id(package):
    return package[6]

def get_tot_len_in_bits(package):
    x = package[7:22]
    padding = np.zeros((1,), dtype=bool)
    x = np.concatenate((padding, x), axis=0)
    return np.sum(np.packbits(x))

def get_tot_num_sub_packages(package):
    x = package[7:19]
    y = 2**np.arange(x.shape[0] - 1, -1, -1)
    print(np.arange(x.size - 1, -1, -1))
    print(np.sum(x * y.T))
    return np.sum(x * y.T)


def read_package():
    return np.array([int(x) for x in sys.stdin.readline() if x != '\n'], dtype=bool)

def hex_to_bitstring(hex_string):
    return "".join([format(int(x, 16), "04b") for x in hex_string])

def log(tc, message):
    return "(" + str(tc) + ") " + message

def main():
    print(read_package())
    
def test():
    #########################################
    # tc_1
    #########################################
    hex_string = '38006F45291200'
    bit_string = hex_to_bitstring(hex_string)
    assert bit_string == '00111000000000000110111101000101001010010001001000000000', log(1, "failed to convert hex string to bit string")

    package = np.fromiter((int(x) for x in bit_string), dtype=bool)
    assert get_version(package) == 1, log(1,"failed to get version number")
    assert get_type_id(package) == 6, log(1, "failed to get type id")
    assert get_length_type_id(package) == 0, log(1, "failed to get length type id")
    assert get_tot_len_in_bits(package) == 27, log(1, "failed to get total number of bits")

    #########################################
    # tc_2
    #########################################
    hex_string = 'EE00D40C823060'
    bit_string = hex_to_bitstring(hex_string)
    assert bit_string == '11101110000000001101010000001100100000100011000001100000', log(2, "failed to convert hex string to bit string")
    
    package = np.fromiter((int(x) for x in bit_string), dtype=bool)
    assert get_version(package)        == 7, log(2, "failed to get version number")
    assert get_type_id(package)        == 3, log(2, "failed to get type id")
    assert get_length_type_id(package) == 1, log(2, "failed to get length type id")
    assert get_tot_num_sub_packages(package) == 3, log(2, "failed to get the total number of sub-packages")
    #########################################
if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('-t', dest='test', action='store_true')
    args = parser.parse_args()
    if args.test:
        test()
    else:
        main()