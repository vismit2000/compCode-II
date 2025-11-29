# Coordinate compression - Then Dijkstra on complex plane with walls

import heapq


def solve():
    instructions = [
        (p[0], int(p[1:])) for p in open("input.txt").read().strip().split(",")
    ]

    pos, direction, segments = 0j, 1 + 0j, []
    x_coords, y_coords = {0}, {0}

    for turn, length in instructions:
        direction *= -1j if turn == "R" else 1j
        start_pos = pos
        pos += direction * length
        segments.append((start_pos, pos))
        x_coords.update([int(start_pos.real), int(pos.real)])
        y_coords.update([int(start_pos.imag), int(pos.imag)])

    all_x = {x + d for x in x_coords for d in (-1, 0, 1)}
    all_y = {y + d for y in y_coords for d in (-1, 0, 1)}

    sorted_x, sorted_y = sorted(all_x), sorted(all_y)
    map_x = {x: i for i, x in enumerate(sorted_x)}
    map_y = {y: i for i, y in enumerate(sorted_y)}

    # Initialize all grid cells as False (passable)
    grid = {}
    for r in range(len(sorted_x)):
        for c in range(len(sorted_y)):
            grid[r + c * 1j] = False

    # Mark wall segments as True (blocked)
    for start, end in segments:
        cx1, cx2 = map_x[int(start.real)], map_x[int(end.real)]
        cy1, cy2 = map_y[int(start.imag)], map_y[int(end.imag)]
        for r in range(min(cx1, cx2), max(cx1, cx2) + 1):
            for c in range(min(cy1, cy2), max(cy1, cy2) + 1):
                grid[r + c * 1j] = True

    startpoint = map_x[0] + map_y[0] * 1j
    grid[startpoint] = False
    endpoint = map_x[int(pos.real)] + map_y[int(pos.imag)] * 1j
    grid[endpoint] = False

    pq, distances = [(0, (startpoint.real, startpoint.imag))], {startpoint: 0}

    while pq:
        dist, (pos_real, pos_imag) = heapq.heappop(pq)
        pos = pos_real + pos_imag * 1j
        if pos == endpoint:
            return print(f"Shortest path length: {dist}")
        if dist > distances.get(pos, float("inf")):
            continue

        for dir in [1, -1, 1j, -1j]:
            next_pos = pos + dir
            if next_pos in grid and not grid[next_pos]:
                new_dist = (
                    dist
                    + abs(sorted_x[int(next_pos.real)] - sorted_x[int(pos.real)])
                    + abs(sorted_y[int(next_pos.imag)] - sorted_y[int(pos.imag)])
                )
                if new_dist < distances.get(next_pos, float("inf")):
                    distances[next_pos] = new_dist
                    heapq.heappush(pq, (new_dist, (next_pos.real, next_pos.imag)))
    print("No path found.")


solve()
