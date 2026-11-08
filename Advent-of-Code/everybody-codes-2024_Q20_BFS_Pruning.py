# Q: https://everybody.codes/event/2024/quests/20

from collections import deque

with open("input.txt", "r") as file:
    lines = file.read().strip().split("\n")
    graph = {i + j * 1j: c for i, r in enumerate(lines) for j, c in enumerate(r)}
    start = next(p for p in graph if graph[p] == "S")
    A = next(p for p in graph if graph[p] == "A")
    B = next(p for p in graph if graph[p] == "B")
    C = next(p for p in graph if graph[p] == "C")
    checkpoint_order = ["A", "B", "C"]


def bfs(graph):
    Q = deque([(start, 10000, 0, 0, 0)])
    visited = {(start, 0, 0): 10000}

    while Q:
        pos, altitude, _dir, cp, tim = Q.popleft()
        if pos == start and cp == 3 and altitude >= 10000:
            return tim

        for d in (1, 1j, -1, -1j):
            new_pos = pos + d
            if new_pos not in graph or graph[new_pos] == "#" or d + _dir == 0:
                continue
            new_altitude = altitude
            if graph[new_pos] == "+":
                new_altitude += 1
            elif graph[new_pos] == "-":
                new_altitude -= 2
            else:
                new_altitude -= 1
            ncp = cp
            if cp < 3 and graph[new_pos] == checkpoint_order[cp]:
                ncp += 1
            if new_pos == start and ncp == 3 and new_altitude >= 10000:
                return tim + 1
            if visited.get((new_pos, d, ncp), 0) < new_altitude:
                Q.append((new_pos, new_altitude, d, ncp, tim + 1))
                visited[(new_pos, d, ncp)] = altitude
    return -1


print(bfs(graph))
