import sys
from collections import defaultdict

sys.setrecursionlimit(1000000)

content = open("input.txt", "r").read()
lines = content.split("\n")
n, m = len(lines), len(lines[0])

dir = {"^": (-1, 0), "v": (1, 0), "<": (0, -1), ">": (0, 1)}


def all_paths(graph, start, end):
    visited = set()
    paths = []

    def dfs(node, path, weight):
        visited.add(node)
        if node == end:
            paths.append((path, weight))
        for neighbor, wt in graph[node].items():
            if neighbor not in visited:
                dfs(neighbor, path + [neighbor], weight + wt)
        visited.remove(node)

    dfs(start, [start], 0)
    return paths


def condense_graph(points):
    graph = defaultdict(dict)

    for sr, sc in points:
        stack = [(sr, sc, 0)]
        visited = {(sr, sc)}

        while stack:
            r, c, d = stack.pop()
            if d != 0 and (r, c) in points:
                graph[(sr, sc)][(r, c)] = d
                continue

            for dr, dc in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
                nr, nc = r + dr, c + dc
                if (
                    0 <= nr < n
                    and 0 <= nc < m
                    and lines[nr][nc] != "#"
                    and (nr, nc) not in visited
                ):
                    stack.append((nr, nc, d + 1))
                    visited.add((nr, nc))
    return graph


start, end = (0, 1), (n - 1, m - 2)
points = [start, end]
for i in range(n):
    for j in range(m):
        if lines[i][j] == "#":
            continue
        else:
            nbrs = 0
            for dx, dy in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
                nx, ny = i + dx, j + dy
                if 0 <= nx < n and 0 <= ny < m and lines[nx][ny] != "#":
                    nbrs += 1
            if nbrs >= 3:
                points.append((i, j))

graph = condense_graph(points)
paths = all_paths(graph, start, end)
print(max([path[1] for path in paths]))
