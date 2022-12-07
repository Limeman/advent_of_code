import sys
import numpy as np

def read_data():
    ret_val = []
    for line in sys.stdin:
        ret_val.append([l for l in line if l != "\n"])
    return ret_val


def main():
    data = read_data()
    stack = []
    closers = {'(' : ')', '[' : ']', '{' : '}', '<' : '>'}
    scores = {')' : 3, ']' : 57, '}' : 1197, '>' : 25137}
    final_score = 0
    for d in data:
        for c in d:
            if c == '(' or c == '[' or c == '{' or c == '<':
               stack.append(closers[c])
            elif c == stack[-1]:
                stack.pop()
            else:
                final_score += scores[c]
                break
    print("Syntax error score:\t" + str(final_score))
if __name__ == "__main__":
    main()