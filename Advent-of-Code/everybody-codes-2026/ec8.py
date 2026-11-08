with open("../input.txt") as f:
    grid = {
        r + c * 1j: int(ch)
        for r, row in enumerate(f.read().splitlines())
        for c, ch in enumerate(row) if ch.isdigit()
    }

# hex directions as (row + col*1j): ↘ ↙ ← ↖ ↗ →
DIRS = (1 + 1j, 1 - 1j, -2j, -1 - 1j, -1 + 1j, 2j)

# every straight line of hexes along each direction, precomputed
LINES = {}
for d in DIRS:
    LINES[d] = []
    for p in grid:
        if p - d not in grid:  # start of a line
            line = []
            while p in grid:
                line.append(p)
                p += d
            LINES[d].append(line)


def lit(d, h=grid):
    # shadow drops by 1 per hex; height 0 (seed) is never lit and casts nothing
    out = []
    for line in LINES[d]:
        shadow = 0
        for p in line:
            if h[p] > shadow:
                out.append(p)
            shadow = max(shadow, h[p], 1) - 1
    return out


# Part I: energy from the upper left, travelling ↘
print(len(lit(DIRS[0])))

# Part II: one full circuit over all six directions
print(sum(len(lit(d)) for d in DIRS))

# Part III: lit Ents grow; a 9 becomes a warrior and leaves a seed that sprouts 4 rounds later
h, sprout = dict(grid), {}
energy = warriors = rnd = 0
while warriors < 100000:
    rnd += 1
    for p in [p for p, r in sprout.items() if r == rnd]:
        h[p] = 1
        del sprout[p]
    on = lit(DIRS[(rnd - 1) % 6], h)
    energy += len(on)
    for p in on:
        if h[p] == 9:
            h[p], sprout[p] = 0, rnd + 4
            warriors += 1
        else:
            h[p] += 1
print(energy)
