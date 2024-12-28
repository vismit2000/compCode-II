with open("input.txt", "r") as file:
    lines = file.read().strip().split("\n")
    graph = {i + j * 1j: c for i, r in enumerate(lines) for j, c in enumerate(r)}
    start = next(p for p in graph if graph[p] == "S")
    end = next(p for p in graph if graph[p] == "E")


def bfs(point, graph):
    dist = {}
    q = [(point, 0)]
    visited = {point}
    while q:
        p, d = q.pop(0)
        dist[p] = d
        for dir in (-1, 1j, 1, -1j):
            np = p + dir
            if graph.get(np, "#") != "#" and np not in visited:
                q.append((np, d + 1))
                visited.add(np)
    return dist


def neighborhood(point, radius):
    """All points within `radius` of `point` (using taxi distance)."""
    return [
        point + dx + dy * 1j
        for dx in range(-radius, radius + 1)
        for dy in range(-(radius - abs(dx)), radius - abs(dx) + 1)
    ]


def taxi_distance(p1, p2):
    return abs(p1.real - p2.real) + abs(p1.imag - p2.imag)


def cheats(racetrack, lower_bound=1, radius=20):
    """All ways of cheating by taking up to `radius` steps through walls and back to the track."""
    D = bfs(end, racetrack)
    return [
        (p1, p2, t)
        for p1 in D
        for p2 in neighborhood(p1, radius)
        if p2 in D and (t := D[p1] - D[p2] - taxi_distance(p1, p2)) >= lower_bound
    ]


print(len(cheats(graph, 100, 2)))
print(len(cheats(graph, 100, 20)))
