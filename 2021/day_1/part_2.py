import sys

def main():
    increase_count = 0
    decrease_count = 0
    
    values = []
    for line in sys.stdin:
        values.append(int(line))

    prev = 0
    curr = 0
    for i in range(1, len(values) - 1):
        if i == 1:
            prev = values[i - 1] + values[i] + values[i + 1]
        else:
            curr = values[i - 1] + values[i] + values[i + 1]
            
            if curr < prev:
                decrease_count += 1
            elif curr > prev:
                increase_count += 1
            else:
                pass
            prev = curr
    
    print(str(increase_count) + "\tIncreases")
    print(str(decrease_count) + "\tDecreases")




if __name__ == "__main__":
    main()