from collections import Counter

with open("../input.txt") as f:
    grid = {r + c * 1j: ch for r, row in enumerate(f.read().splitlines()) for c, ch in enumerate(row)}

ARROWS = {">": 1j, "v": 1, "<": -1j, "^": -1}  # row + col*1j
walls = {p for p, ch in grid.items() if ch == "#"}


def start(life):
    return [(p, ARROWS[ch], life) for p, ch in grid.items() if ch in ARROWS]


def step(ghosts):
    # move all at once; a wall means stay, turn clockwise and lose a life
    hits, moved = 0, []
    for p, d, life in ghosts:
        if p + d in walls or p + d not in grid:
            hits += 1
            if life > 1:  # a ghost on its last life vanishes before ghost collisions
                moved.append((p, d * -1j, life - 1))
        else:
            moved.append((p + d, d, life))
    # then any shared space turns everyone on it around
    cnt = Counter(p for p, _, _ in moved)
    hits += sum(n for n in cnt.values() if n > 1)
    nxt = [(p, -d, life - 1) if cnt[p] > 1 else (p, d, life) for p, d, life in moved]
    return [g for g in nxt if g[2] > 0], hits


# Part I
ghosts, total = start(float("inf")), 0
for _ in range(10):
    ghosts, hits = step(ghosts)
    total += hits
print(total)

def last_round(life):
    # movement ignores lives, so (positions, directions) repeats; skip whole cycles until a ghost is about to vanish
    ghosts, rnd, seen = start(life), 0, {}
    while ghosts:
        key = tuple((p, d) for p, d, _ in ghosts)
        if key in seen:
            r0, lives0 = seen[key]
            lost = [a - l for a, (_, _, l) in zip(lives0, ghosts)]  # collisions per cycle
            n = min(((l - 1) // k for (_, _, l), k in zip(ghosts, lost) if k), default=0)
            ghosts = [(p, d, l - n * k) for (p, d, l), k in zip(ghosts, lost)]
            rnd += n * (rnd - r0)
            seen = {}
        seen[key] = (rnd, [l for _, _, l in ghosts])
        ghosts, _ = step(ghosts)
        rnd += 1
    return rnd


print(last_round(10000))  # Part II
print(last_round(10**12))  # Part III
