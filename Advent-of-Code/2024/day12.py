with open("input.txt", "r") as file:
    lines = file.read().strip().split("\n")
    n, m = len(lines), len(lines[0])
    graph = {i + j * 1j: c for i, r in enumerate(lines) for j, c in enumerate(r)}
    for i in range(-1, n + 1):
        graph[i - 1 * 1j] = graph[i + m * 1j] = "#"
    for j in range(-1, m + 1):
        graph[-1 + j * 1j] = graph[n + j * 1j] = "#"
    visited = set()


def dfs(visited, node, color, dir):
    if graph[node] != color:
        if graph[node + dir * 1j] == color or graph[node - dir + dir * 1j] != color:
            return 0, 1, 1
        else:
            return 0, 1, 0
    if node in visited:
        return 0, 0, 0
    visited.add(node)
    area, perimeter, sides = 1, 0, 0
    for d in (1, -1, 1j, -1j):
        a, p, s = dfs(visited, node + d, color, d)
        area, perimeter, sides = area + a, perimeter + p, sides + s
    return area, perimeter, sides


ans1, ans2 = 0, 0
for node in graph:
    if node not in visited and graph[node] != "#":
        area, perimeter, sides = dfs(visited, node, graph[node], 1)
        ans1 += area * perimeter
        ans2 += area * sides
print(ans1, ans2)