from os import read
import sys

def read_data():
    pair_insertions = {}
    starting_string = "asdf"
    for line in sys.stdin:
        if line[-1] == '\n':
            line = line[:-1]
        
        if "->" not in line:
            if line != '':
                starting_string = line
        else:
            [pair, insertion] = line.split(" -> ")
            pair_insertions[pair] = insertion
            
    return pair_insertions, starting_string

def insert(pair_insertions, pair, tmp_string):
    for k, v in pair_insertions:
        if pair == k:
            pass

def polymerize(pair_insertions, curr_string, iterations):
    tmp_string = curr_string
    for _ in range(iterations):
        j = 0
        for i in range(len(curr_string) - 2 + 1):
            pair = curr_string[i:i + 2]
            if pair in pair_insertions.keys():
                tmp_string = tmp_string[:i + j + 1] + pair_insertions[pair] + tmp_string[i + j + 1:]
                j += 1
        curr_string = tmp_string
    return curr_string

def count_occurances(poly_chain):
    occurances = {}
    for p in poly_chain:
        if p in occurances:
            occurances[p] += 1
        else:
            occurances[p] = 1
    return occurances

def main():
    pair_insertions, starting_string = read_data()
    poly_chain = polymerize(pair_insertions, starting_string, 10)
    occurances = count_occurances(poly_chain)
    print("Score:\t" + str(max(occurances.values()) - min(occurances.values())))

if __name__ == "__main__":
    main()