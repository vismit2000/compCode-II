# Hex grid: https://www.redblobgames.com/grids/hexagons/

import re
from collections import defaultdict, Counter
from itertools import chain

flatten = chain.from_iterable

content = open("input.txt", "r").read()
instructions = content.splitlines()

hexdirs = dict(e=(1, 0), w=(-1, 0), ne=(1, -1), sw=(-1, 1), se=(0, 1), nw=(0, -1))


def parse_hex(line) -> list[str]:
    return re.findall("e|w|ne|sw|se|nw", line)


def follow_hex(directions: str):
    "What (x, y) location do you end up at after following directions?"
    x, y = 0, 0
    for dir in parse_hex(directions):
        dx, dy = hexdirs[dir]
        x += dx
        y += dy
    return (x, y)


def neighborhood(point) -> list[tuple]:
    x, y = point
    return [(x + dx, y + dy) for dx, dy in hexdirs.values()]


def next_generation(cells) -> set[tuple]:
    neighbor_counts = Counter(flatten(map(neighborhood, cells)))
    return {c for c in cells if neighbor_counts[c] in (1, 2)} | {
        c for c in neighbor_counts if c not in cells and neighbor_counts[c] == 2
    }


def simulate(cells, n=100) -> set[tuple]:
    for gen in range(n):
        cells = next_generation(cells)
    return cells


def part_1():
    d = defaultdict(int)
    for instr in instructions:
        x, y = follow_hex(instr)
        d[(x, y)] += 1
    ans = 0
    for k, v in d.items():
        if v % 2 == 1:
            ans += 1
    print(ans)


def part_2():
    counts = Counter(map(follow_hex, instructions))
    blacks = {tile for tile in counts if counts[tile] % 2}
    print(len(simulate(blacks)))
