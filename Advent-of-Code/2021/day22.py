# Coordinate compression

content = open("input.txt", "r").read()

from collections import namedtuple

Step = namedtuple("Step", ["type", "x1", "x2", "y1", "y2", "z1", "z2"])

steps, X, Y, Z = [], [], [], []
for line in content.splitlines():
    type, coords = line.split()
    coords = [coord[2:] for coord in coords.split(",")]
    x1, x2 = map(int, coords[0].split(".."))
    y1, y2 = map(int, coords[1].split(".."))
    z1, z2 = map(int, coords[2].split(".."))
    x2, y2, z2 = x2 + 1, y2 + 1, z2 + 1
    steps.append(Step(type, x1, x2, y1, y2, z1, z2))
    X.extend([x1, x2])
    Y.extend([y1, y2])
    Z.extend([z1, z2])

X, Y, Z = sorted(set(X)), sorted(set(Y)), sorted(set(Z))

grid = {}
for step in steps:
    for x in range(X.index(step.x1), X.index(step.x2)):
        for y in range(Y.index(step.y1), Y.index(step.y2)):
            for z in range(Z.index(step.z1), Z.index(step.z2)):
                grid[(x, y, z)] = 1 if step.type == "on" else 0

ans = 0
for (x, y, z), val in grid.items():
    ans += val * (X[x + 1] - X[x]) * (Y[y + 1] - Y[y]) * (Z[z + 1] - Z[z])
print(ans)
