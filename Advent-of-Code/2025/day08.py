# alternate (using networkx): https://github.com/hughcoleman/advent-of-code/blob/main/2025/08.py

from collections import defaultdict
from math import prod

with open("input.txt") as f:
    lines = f.read().strip().split("\n")
    points = [tuple(map(int, line.split(","))) for line in lines]

class DSU:
    def __init__(self, n):
        self.parent = list(range(n))
        self.size = [1] * n

    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])  # path compression
        return self.parent[x]

    def union(self, x, y):
        xr, yr = self.find(x), self.find(y)
        if xr == yr:
            return False  # already in same component
        if self.size[xr] < self.size[yr]:
            xr, yr = yr, xr
        self.parent[yr] = xr
        self.size[xr] += self.size[yr]
        return True

def euclidean(p1, p2):
    return sum((pi - pj) ** 2 for pi, pj in zip(p1, p2))

distances = []
for i in range(len(points)):
    for j in range(i+1, len(points)):
        distances.append((euclidean(points[i], points[j]), i, j))

distances.sort()
dsu = DSU(len(points))

# for i in range(1000):
#     dsu.union(distances[i][1], distances[i][2])

# set_sizes = defaultdict(int)
# for i in range(len(points)):
#     set_sizes[dsu.find(i)] += 1

# print(prod(sorted(list(set_sizes.values()))[-3:]))

mst_edges = []
for w, u, v in distances:
    if dsu.union(u, v):
        mst_edges.append((u, v))
        if len(mst_edges) == len(points) - 1:
            break

print(points[mst_edges[-1][0]][0] * points[mst_edges[-1][1]][0])