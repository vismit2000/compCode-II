from collections import defaultdict
from itertools import combinations
from math import gcd

with open("input.txt", "r") as file:
    lines = file.read().strip().split("\n")
    graph = {i + j * 1j: c for i, r in enumerate(lines) for j, c in enumerate(r)}

antennas = defaultdict(list)
for k, v in graph.items():
    if v != ".":
        antennas[v].append(k)

antinodes_1, antinodes_2 = set(), set()
for points in antennas.values():
    for p1, p2 in combinations(points, 2):
        a1, a2 = 2 * p1 - p2, 2 * p2 - p1
        dir = p2 - p1
        dir = dir / gcd(int(dir.real), int(dir.imag))
        if a1 in graph:
            antinodes_1.add(a1)
        if a2 in graph:
            antinodes_1.add(a2)
        p = p1
        while p in graph:
            antinodes_2.add(p)
            p += dir
        p = p2
        while p in graph:
            antinodes_2.add(p)
            p -= dir
print(len(antinodes_1), len(antinodes_2))