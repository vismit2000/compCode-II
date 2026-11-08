import re
from collections import Counter

energy, conn = {}, {}
for line in open("../input.txt").read().splitlines():
    cid, e, cs = re.match(r"id=(\w+), energy=(-?\d+), connections=(.*)", line).groups()
    energy[cid], conn[cid] = int(e), [c for c in cs.split(",") if c]


def propagate(strength):
    # track how many impulses sit on each cloud at each strength
    total = sum(energy.values())
    cur = Counter([max(conn, key=lambda c: len(conn[c]))])
    for s in range(strength, 0, -1):
        total += s * sum(cur.values())
        nxt = Counter()
        for c, n in cur.items():
            for d in conn[c]:
                nxt[d] += n
        cur = nxt
    return total


def duel(start, limit=1000000):
    # impulses keyed by (cloud, strength), since explosions mix strengths in one stage
    en, dead = dict(energy), set()
    cur = Counter({(start, 10): 1})
    while cur:
        nxt = Counter()
        for (c, s), n in cur.items():
            if c in dead:
                continue
            en[c] += s * n
            if s > 1:
                for d in conn[c]:
                    nxt[d, s - 1] += n
        for c in {c for c, _ in cur} - dead:
            if en[c] >= limit:
                dead.add(c)
                for d in conn[c]:
                    nxt[d, 10] += 1
        cur = nxt
    return sum(e for c, e in en.items() if c not in dead)


print(propagate(5))  # Part I
print(propagate(10))  # Part II
print(max(duel(c) for c in conn))  # Part III
