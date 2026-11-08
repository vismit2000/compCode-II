from collections import deque

with open("../input.txt", "r") as file:
    lines = file.read().strip().split("\n")
    graph = {i + j * 1j: c for i, r in enumerate(lines) for j, c in enumerate(r)}
    centre = len(lines) // 2 + len(lines[0]) // 2 * 1j

DIRS = (1, 1j, -1, -1j, 1 + 1j, 1 - 1j, -1 + 1j, -1 - 1j)


def bfs(seed, allowed, support):
    # grow `seed` into `allowed` cells with >= 5 neighbours in found | support
    found = set(seed)
    Q = deque(p + d for p in found for d in DIRS)

    while Q:
        pos = Q.popleft()
        if pos not in allowed or pos in found:
            continue
        if sum(p in found or p in support for p in (pos + d for d in DIRS)) >= 5:
            found.add(pos)
            # neighbours may now have enough support, so recheck them
            Q.extend(pos + d for d in DIRS)
    return found


# Part I
dark = {p for p in graph if graph[p] == "1"}
land = bfs({centre}, graph, dark)
print(len(land))

# Part II: off-map cells are not in `land`, so they count as water
coast = {p for p in land if any(p + d not in land for d in DIRS)}
sand = bfs(coast, land, set())
print(len(sand))

# Part III: every `+` must be land or tree, i.e. in land - sand, so stamp order doesn't matter
inner = land - sand
STAMP = [a + b * 1j for a in range(-2, 3) for b in range(-2, 3) if abs(a) + abs(b) not in (0, 4)]
trees = {p for p in inner if all(p + s in inner for s in STAMP)}

for _ in range(2):
    trees |= {
        p for p in inner - trees
        if sum(p + d in trees for d in DIRS) >= 4 and not any(p + d in sand for d in DIRS)
    }
print(len(trees))
