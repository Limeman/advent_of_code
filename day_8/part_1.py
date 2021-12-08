import sys
import numpy as np
from numpy.core.numeric import ones

def read_data():
    signal_patterns = []
    output_values = []
    for line in sys.stdin:
        [str_signal_patterns, str_output_values] = line.split(" | ")
        signal_patterns.append([x for x in str_signal_patterns.split(" ")])
        str_output_values = "".join([x for x in str_output_values if x != "\n"])
        output_values.append([x for x in str_output_values.split(" ")])
    return signal_patterns, output_values

def main():
    _, output_values = read_data()
    final_count = 0
    for line in output_values:
        for o in line:
            #             1  4  7  8
            if len(o) in (2, 4, 3, 7):
                final_count += 1
    print(final_count)



if __name__ == "__main__":
    main()