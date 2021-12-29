import sys
from collections import Counter

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
    chars = Counter(curr_string)
    old_pairs = {}
    for i in range(len(curr_string) - 2 + 1):
        pair = curr_string[i:i + 2]
        if pair in old_pairs.keys():
            old_pairs[pair] += 1
        else:
            old_pairs[pair] = 1
    
    for curr_iteration in range(iterations):
        curr_pairs = Counter()
        for k, v in old_pairs.items():
            [x, y] = [k[0], k[1]]
            insert = pair_insertions[k]
            curr_pairs[x + insert] += v
            curr_pairs[insert + y] += v
            chars[insert] += v
        old_pairs = curr_pairs
        print("Current iteration:\t" + str(curr_iteration))

    return max(chars.values()) - min(chars.values()) 

def main():
    pair_insertions, starting_string = read_data()
    print("Score:\t" + str(polymerize(pair_insertions, starting_string, 40)))

if __name__ == "__main__":
    main()