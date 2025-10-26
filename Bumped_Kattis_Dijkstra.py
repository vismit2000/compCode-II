# https://open.kattis.com/problems/bumped

import heapq
from collections import defaultdict


def dijkstra(num_cities, roads, flights, start, end):
    road_graph = defaultdict(list)
    flight_graph = defaultdict(list)

    for u, v, cost in roads:
        road_graph[u].append((v, cost))
        road_graph[v].append((u, cost))
    for u, v in flights:
        flight_graph[u].append(v)
        flight_graph[v].append(u)

    min_cost = {}
    min_cost[(start, False)] = 0
    pq = [(0, start, False)]

    while pq:
        current_cost, city, used = heapq.heappop(pq)
        if city == end:
            return current_cost

        for neighbor, travel_cost in road_graph[city]:
            new_cost = current_cost + travel_cost
            if new_cost < min_cost.get((neighbor, used), float("inf")):
                min_cost[(neighbor, used)] = new_cost
                heapq.heappush(pq, (new_cost, neighbor, used))

        if not used:
            for neighbor in flight_graph[city]:
                if current_cost < min_cost.get((neighbor, True), float("inf")):
                    min_cost[(neighbor, True)] = current_cost
                    heapq.heappush(pq, (current_cost, neighbor, True))
                heapq.heappush(pq, (current_cost, neighbor, True))

    return -1


with open("input.txt", "r") as file:
    data = file.read().strip().splitlines()
    t = int(data[0])
    line_idx = 1

    for _ in range(t):
        n, m, f, s, e = map(int, data[line_idx].split())
        line_idx += 1

        roads = [tuple(map(int, data[line_idx + i].split())) for i in range(m)]
        line_idx += m

        flights = [tuple(map(int, data[line_idx + i].split())) for i in range(f)]
        line_idx += f

        result = dijkstra(n, roads, flights, s, e)
        print(result)
