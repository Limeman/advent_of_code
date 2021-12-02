import sys

def forward(pos, steps):
    return (pos[0] + steps, pos[1] + steps * pos[2], pos[2])

def down(pos, steps):
    return (pos[0], pos[1], pos[2] + steps)

def up(pos, steps):
    return (pos[0], pos[1], pos[2] - steps)


def main():
    curr_pos = (0, 0, 0)
    for line in sys.stdin:
        [action, str_steps] = line.split()
        steps = int(str_steps)

        if action == 'forward':
            curr_pos = forward(curr_pos, steps)
        elif action == 'down':
            curr_pos = down(curr_pos, steps)
        else:
            curr_pos = up(curr_pos, steps)
    print("Horzontal pos:\t" + str(curr_pos[0]) + "\nDepth:\t\t" + str(curr_pos[1]) + "\nAim:\t\t" + str(curr_pos[2]))
    print("Multiplied:\t" + str(curr_pos[0] * curr_pos[1]))

if __name__ == "__main__":
    main()