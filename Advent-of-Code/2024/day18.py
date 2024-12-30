import re

with open("input.txt", "r") as file:
    lines = file.read().strip().split("\n")
    coords = [tuple(map(int, re.findall(r"\d+", line))) for line in lines]
    n = max(max(x, y) for x, y in coords) + 1
    m = 12 if n == 7 else 1024

    graph = {i + j * 1j: "." for i in range(n) for j in range(n)}
    for x, y in coords[:m]:
        graph[x + y * 1j] = "#"


def shortest_path_bfs(graph, start, end):
    queue = [(start, 0)]
    visited = {start}
    while queue:
        pos, dist = queue.pop(0)
        if pos == end:
            return dist
        for d in (1, 1j, -1, -1j):
            new_pos = pos + d
            if new_pos in graph and new_pos not in visited and graph[new_pos] != "#":
                queue.append((new_pos, dist + 1))
                visited.add(new_pos)
    return -1


print(shortest_path_bfs(graph, 0, (n - 1) + (n - 1) * 1j))

lo, hi, ans = 0, len(coords) - 1, 0
while lo <= hi:
    mid = (lo + hi) // 2
    graph = {i + j * 1j: "." for i in range(n) for j in range(n)}
    for x, y in coords[:mid]:
        graph[x + y * 1j] = "#"
    if shortest_path_bfs(graph, 0, (n - 1) + (n - 1) * 1j) != -1:
        ans, lo = mid, mid + 1
    else:
        hi = mid - 1
print(*coords[ans], sep=",")