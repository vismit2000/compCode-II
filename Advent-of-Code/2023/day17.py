import heapq

content = open("input.txt", "r").read()
lines = content.split("\n")
n, m = len(lines), len(lines[0])

graph = [list(map(int, line.strip())) for line in lines]


def dijkstra(graph, src, dest, part):
    dist = {}
    heap = [(0, src, -1, 0)]

    while heap:
        d, node, prev_dir, prev_dir_count = heapq.heappop(heap)
        if node == dest and (part == 1 or prev_dir_count >= 4):
            return d
        if (node, prev_dir, prev_dir_count) in dist:
            continue
        dist[node, prev_dir, prev_dir_count] = d

        for next_dir, (dx, dy) in enumerate(([0, 1], [1, 0], [0, -1], [-1, 0])):
            nx, ny = node[0] + dx, node[1] + dy
            new_dir_count = 1 if next_dir != prev_dir else prev_dir_count + 1
            part_cond = {
                1: new_dir_count <= 3,
                2: new_dir_count <= 10
                and (next_dir == prev_dir or prev_dir_count >= 4 or node == src),
            }
            if (
                0 <= nx < n
                and 0 <= ny < m
                and (prev_dir + 2) % 4 != next_dir
                and part_cond[part]
            ):
                heapq.heappush(
                    heap, (d + graph[nx][ny], (nx, ny), next_dir, new_dir_count)
                )


print(dijkstra(graph, (0, 0), (n - 1, m - 1), 1))
print(dijkstra(graph, (0, 0), (n - 1, m - 1), 2))
