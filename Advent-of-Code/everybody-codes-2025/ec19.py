import heapq
from collections import defaultdict

with open("input.txt") as f:
    lines = f.read().strip().split("\n")
    segments = [tuple(map(int, line.split(","))) for line in lines]
    segments.sort()
    WIDTH = max(segment[0] for segment in segments)
    HEIGHT = max(segment[1] + segment[2] for segment in segments)
    openings = defaultdict(list)
    for x, y, length in segments:
        openings[x].append((y, y + length))
    for x in range(WIDTH+1):
        if not openings[x]:
            openings[x].append((0, HEIGHT+1))

def valid_move(node, neighbor, openings):
    if neighbor.real < 0 or neighbor.imag < 0 or neighbor.real > HEIGHT or neighbor.imag > WIDTH:
        return False
    # Check if both node and neighbor are within any opening at their respective x-coordinates
    node_open = any(start <= node.real < end for start, end in openings[int(node.imag)])
    neighbor_open = any(start <= neighbor.real < end for start, end in openings[int(neighbor.imag)])
    return node_open and neighbor_open

def dijkstra(start):
    dist = {start: 0 }
    pq = [(0, (start.real, start.imag))]

    while pq:
        d, pos = heapq.heappop(pq)
        node = complex(pos[0], pos[1])
        for cost, dir in [(0, (-1 + 1j)), (1, (1 + 1j))]:
            neighbor = node + dir
            if valid_move(node, neighbor, openings) and d + cost < dist.get(neighbor, float('inf')):
                dist[neighbor] = d + cost
                heapq.heappush(pq, (d + cost, (neighbor.real, neighbor.imag)))
    return dist

dist = dijkstra(0)
# print(dist)
print(min(dist.get(x + WIDTH * 1j, float('inf')) for opening in openings[WIDTH] for x in range(opening[0], opening[1])))