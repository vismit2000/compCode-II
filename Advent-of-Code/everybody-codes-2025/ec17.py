# Dijkstra's algorithm with state tracking to find the minimum time to reach the start point making a loop
from math import sqrt, ceil
import heapq

with open("input.txt") as f:
    lines = f.read().strip().split("\n")
    graph = {i + j * 1j: c for i, r in enumerate(lines) for j, c in enumerate(r)}
    volcano = next(p for p in graph if graph[p] == "@")
    start = next(p for p in graph if graph[p] == "S")
    graph[start] = '0'

def dist_volcano(i, j, volcano):
    return (i - volcano.real) ** 2 + (j - volcano.imag) ** 2

def dijkstra(src, graph):
    dist = {}
    dist[(src, 0)] = 0
    pq = [(0, (src.real, src.imag), 0, 0)]

    while pq:
        d, (node_real, node_imag), z, prev_dir = heapq.heappop(pq)
        node = complex(node_real, node_imag)
        if node == start and z == 1:
            return d
        
        for dir in (1, -1, 1j, -1j):
            neighbor = node + dir
            if neighbor in graph:
                new_dist = d + int(graph[neighbor])
                new_z = z
                if node.imag == volcano.imag and node.real > volcano.real and dir == prev_dir:
                    new_z = 1 - z
                if new_dist < dist.get((neighbor, new_z), float('inf')):
                    dist[(neighbor, new_z)] = new_dist
                    heapq.heappush(pq, (new_dist, (neighbor.real, neighbor.imag), new_z, dir if dir in (1j, -1j) else prev_dir))

    return -1

RADIUS = 0
while True:
    # erase cells from grid with RADIUS R
    for i in range(int(volcano.real) - RADIUS, int(volcano.real) + RADIUS + 1):
        for j in range(int(volcano.imag) - RADIUS, int(volcano.imag) + RADIUS + 1):
            if i + j * 1j in graph and ceil(sqrt(dist_volcano(i, j, volcano))) == RADIUS:
                del graph[i + j * 1j]

    min_path_length = dijkstra(start, graph)
    if min_path_length < 30 * (RADIUS + 1):
        min_time = min_path_length * RADIUS
        break
    RADIUS += 1
print(min_time)