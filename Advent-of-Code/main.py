import re
import sys
sys.setrecursionlimit(10000)

with open("input.txt") as f:
    lines = f.read().splitlines()

clay, flowing, settled = set(), set(), set()
seen = set()

for line in lines:
    a, b0, b1 = map(int, re.findall(r'\d+', line))
    for b in range(b0, b1 + 1):
        x, y = (a, b) if line[0] == 'x' else (b, a)
        clay.add(x + y*1j)

min_y = int(min(p.imag for p in clay))
max_y = int(max(p.imag for p in clay))

DOWN, LEFT, RIGHT = 1j, -1, 1


def blocked(p):
    return p in clay or p in settled


def flow(p):
    if p.imag > max_y or p in settled or p in seen:
        return
    seen.add(p)

    flowing.add(p)

    # fall down
    if not blocked(p + DOWN):
        flow(p + DOWN)

    # spread left
    L = p
    while not blocked(L + LEFT) and blocked(L + DOWN):
        L += LEFT
        flowing.add(L)

    # spread right
    R = p
    while not blocked(R + RIGHT) and blocked(R + DOWN):
        R += RIGHT
        flowing.add(R)

    # leak
    if not blocked(L + DOWN):
        flow(L + DOWN)
    if not blocked(R + DOWN):
        flow(R + DOWN)

    # settle
    if blocked(L + LEFT) and blocked(R + RIGHT):
        y = p.imag
        for x in range(int(L.real), int(R.real) + 1):
            flowing.discard(x + y*1j)
            settled.add(x + y*1j)

        flow(p - DOWN)


flow(500 + 0j)

print(sum(min_y <= p.imag <= max_y for p in flowing | settled))
print(sum(min_y <= p.imag <= max_y for p in settled))