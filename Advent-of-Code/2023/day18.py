content = open("input.txt", "r").read()
lines = content.split("\n")
n, m = len(lines), len(lines[0])

dir = {"L": (0, -1), "R": (0, 1), "U": (-1, 0), "D": (1, 0)}
plan = [(dir[d], int(n), c[2:-1]) for d, n, c in [line.split() for line in lines]]


def polygon_area(vertices):
    n = len(vertices)
    area = 0.0
    for i in range(n):
        j = (i + 1) % n
        area += vertices[i][0] * vertices[j][1]
        area -= vertices[j][0] * vertices[i][1]

    return abs(area) / 2.0


def lava_pick(plan, part=1):
    x, y, B = 0, 0, 0
    coords = []

    for d, n, c in plan:
        if part == 2:
            n = int(c[:-1], 16)
            d = dir["RDLU"[int(c[-1])]]
        x += d[0] * n
        y += d[1] * n
        B += n
        coords.append((x, y))

    A = polygon_area(coords)
    I = A - B / 2 + 1
    return I + B


print(lava_pick(plan, 1))
print(lava_pick(plan, 2))
