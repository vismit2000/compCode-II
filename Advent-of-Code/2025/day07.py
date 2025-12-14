from functools import cache

with open("input.txt") as f:
    lines = f.read().strip().split("\n")
    graph = {i + j * 1j: c for i, r in enumerate(lines) for j, c in enumerate(r)}
    start = next(p for p in graph if graph[p] == "S")

def fall(p):
    while graph.get(p) != "^" and p + 1 in graph:
        p += 1
    return p

def bfs(point):
    q, visited, splitter = [point], {point}, 0
    while q:
        p = q.pop(0)
        if graph[p] == "^":
            splitter += 1
            dirs = [-1j, 1j]
        else:
            dirs = [1]
        for d in dirs:
            if (n := p + d) in graph and n not in visited:
                q.append(n)
                visited.add(n)
    return splitter

@cache
def timelines(point):
    left, right = fall(point - 1j), fall(point + 1j)

    left_tl = 1 if graph.get(left) != "^" else timelines(left)
    right_tl = 1 if graph.get(right) != "^" else timelines(right)

    return left_tl + right_tl

start = fall(start)
print(bfs(start))
print(timelines(start))