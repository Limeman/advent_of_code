import sys

def main():
    increase_count = 0
    decrease_count = 0
    prev = int(sys.stdin.readline())

    for line in sys.stdin:
        value = int(line)
        
        if prev > value:
            decrease_count = decrease_count + 1
        elif prev < value:
            increase_count = increase_count + 1
        else:
            pass
        prev = value
    
    print(str(increase_count) + "\tIncreases")
    print(str(decrease_count) + "\tDecreases")




if __name__ == "__main__":
    main()