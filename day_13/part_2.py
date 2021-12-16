import sys
import numpy as np

def get_input():
    at_instructions = False
    points = []
    folds = []
    for line in sys.stdin:
        if len(line) == 1:
            at_instructions = True
            continue
        if not at_instructions:
            [x, y] = line.split(",")
            y = "".join([z for z in y if z != "\n"])
            points.append([int(x), int(y)])
        else:
            if line[11] == 'x':
                [_, rest] = line.split("=")
                rest = "".join([z for z in rest if z != "\n"])
                folds.append((int(rest), -1))
            else:
                [_, rest] = line.split("=")
                rest = "".join([z for z in rest if z != "\n"])
                folds.append((-1, int(rest)))
    points = np.array(points)
    max_x, max_y = points[:, 0].max(), points[:, 1].max()
    dots = np.zeros((max_x + 1, max_y + 1), dtype=bool)
    dots[points[:, 0], points[:, 1]] = True
    return dots, folds

def print_dots(dots):
    line = ""
    for j in range(dots.shape[1]):
        for i in range(dots.shape[0]):
            if dots[i, j] == 0:
                line += "."
            else:
                line += "#"
        line += "\n"
    print(line)


def main():
    dots, folds = get_input()
    for f in folds:
        if f[0] == -1:
            y = f[1]
            dots = np.flip(dots[:, y + 1:], 1) | dots[:, :y]
        else:
            x = f[0]
            dots = np.flip(dots[x + 1:, :], 0) | dots[:x, :]
    print_dots(dots)

if __name__ == "__main__":
    main()