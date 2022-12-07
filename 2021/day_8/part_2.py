import sys

def read_data():
    signal_patterns = []
    output_values = []
    for line in sys.stdin:
        [str_signal_patterns, str_output_values] = line.split(" | ")
        signal_patterns.append(["".join(sorted(x)) for x in str_signal_patterns.split(" ")])
        str_output_values = "".join([x for x in str_output_values if x != "\n"])
        output_values.append(["".join(sorted(x)) for x in str_output_values.split(" ")])
    return signal_patterns, output_values

def get_displays_for_count(signal_patterns, count):
    return [s for s in signal_patterns if len(s) == count]

def remove_intersection(s1, s2):
    return "".join([s for s in s1 if s not in s2])

def get_mapping(signal_patterns):
    mapping = {0 : "",
               1 : "",
               2 : "",
               3 : "",
               4 : "",
               5 : "",
               6 : "",
               7 : "",
               8 : "",
               9 : ""}
    mapping[1] = get_displays_for_count(signal_patterns, 2)[0] # 1
    mapping[4] = get_displays_for_count(signal_patterns, 4)[0] # 4
    mapping[7] = get_displays_for_count(signal_patterns, 3)[0] # 7
    mapping[8] = get_displays_for_count(signal_patterns, 7)[0] # 8

    five_segment = get_displays_for_count(signal_patterns, 5)
    six_segment  = get_displays_for_count(signal_patterns, 6)

    mapping[3] = [x for x in five_segment if len(remove_intersection(x, mapping[7])) == 2][0]

    mapping[6] = [x for x in six_segment if len(remove_intersection(x, mapping[7])) == 4][0]
    mapping[9] = [x for x in six_segment if len(remove_intersection(x, mapping[4])) == 2][0]
    mapping[0] = [x for x in six_segment if x != mapping[6] and x != mapping[9]][0]

    mapping[5] = [x for x in five_segment if len(remove_intersection(x, mapping[6])) == 0][0]
    mapping[2] = [x for x in five_segment if x != mapping[5] and x != mapping[3]][0]

    return dict((v,k) for k,v in mapping.items())


def main():
    signal_patterns, output_values = read_data()

    final_count = 0
    for i, s in enumerate(signal_patterns):
        mapping = get_mapping(s)
        for j, o in enumerate(output_values[i]):
            #print(mapping[o])
            final_count += mapping[o] * pow(10, 3 - j)
    print(final_count)




if __name__ == "__main__":
    main()