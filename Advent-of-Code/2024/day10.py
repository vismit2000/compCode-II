from collections import defaultdict

with open("input.txt", "r") as file:
    lines = file.read().strip().split("\n")
    graph = {i + j * 1j: int(c) for i, r in enumerate(lines) for j, c in enumerate(r)}

positions = defaultdict(list)
for k, v in graph.items():
    positions[v].append(k)

# counts = graph.copy()
# for k, v in graph.items():
#     if v == 9:
#         counts[k] = 1
#     else:
#         counts[k] = 0

# for height in range(8, -1, -1):
#     for pos in positions[height]:
#         for dir in (1, 1j, -1, -1j):
#             if graph.get(pos + dir) == height + 1:
#                 counts[pos] += counts[pos + dir]

# print(sum(counts[zero] for zero in positions[0]))


def dfs(pos, visited):
    if pos in visited:
        return 0
    if graph[pos] == 9:
        visited.add(pos)
    if graph[pos] == 9:
        return 1
    return sum(
        dfs(pos + dir, visited)
        for dir in (1, 1j, -1, -1j)
        if graph.get(pos + dir) == graph[pos] + 1
    )


print(sum(dfs(zero, set()) for zero in positions[0]))