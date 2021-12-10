import sys
from statistics import median

def read_data():
    ret_val = []
    for line in sys.stdin:
        ret_val.append([l for l in line if l != "\n"])
    return ret_val

def compute_score(str):
    ret_val = 0
    scores = {')' : 1, ']' : 2, '}' : 3, '>' : 4}
    for s in reversed(str):
        ret_val = ret_val * 5 + scores[s]
    return ret_val

def main():
    data = read_data()
    stack = []
    closers = {'(' : ')', '[' : ']', '{' : '}', '<' : '>'}
    scores = {')' : 1, ']' : 2, '}' : 3, '>' : 4}
    
    autocomplete_scores = []
    for d in data:
        broken = False
        for c in d:
            if c == '(' or c == '[' or c == '{' or c == '<':
               stack.append(closers[c])
            elif c == stack[-1]:
                stack.pop()
            else:
                broken = True
                break
        if not broken:
            autocomplete_scores.append(compute_score(stack))
        stack = []
    print("Middle score:\t" + str(median(autocomplete_scores)))
if __name__ == "__main__":
    main()