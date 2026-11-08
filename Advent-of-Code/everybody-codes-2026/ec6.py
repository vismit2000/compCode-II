from collections import Counter, deque

g, rev = {}, {}
for line in open("../input.txt").read().split():
    item, ings = line.split(":")
    g[item] = ings.split(",")
    for ing in g[item]:
        rev.setdefault(ing, []).append(item)


def bfs(graph, start):
    # everything reachable from start, excluding start itself
    seen, Q = set(), deque([start])
    while Q:
        for nxt in graph.get(Q.popleft(), []):
            if nxt not in seen:
                seen.add(nxt)
                Q.append(nxt)
    return seen - {start}


# Part I: ingredients used to make NULL
print(len(bfs(g, "NULL")))

# Part II: products made using NULL
print(len(bfs(rev, "NULL")))

# Part III: products reached backwards from at least two NULL versions
cnt = Counter(p for v in rev if v.startswith("NULL") for p in bfs(rev, v))
print(sum(c >= 2 for c in cnt.values()))
