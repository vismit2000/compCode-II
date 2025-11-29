with open("input.txt") as f:
    lines = f.read().strip().split("\n")
    graph = {i + j * 1j: c for i, r in enumerate(lines) for j, c in enumerate(r)}
    start = next(p for p in graph if graph[p] == "S")

def rotate(grid):
    def _rot_list(g):
        n_rows, n_cols = len(g), len(g[0])
        out = [["." for _ in range(n_cols)] for _ in range(n_rows)]
        for c in range(0, n_cols, 2):
            dst_r = c // 2
            dst_c = n_cols - 1 - c // 2
            for r in range(n_rows):
                a = r + c
                if a < n_cols and g[r][a] != ".":
                    out[dst_r][dst_c] = g[r][a]
                    dst_c -= 1
                b = a + 1
                if b < n_cols and g[r][b] != ".":
                    out[dst_r][dst_c] = g[r][b]
                    dst_c -= 1
        return out

    if isinstance(grid, list) and grid and isinstance(grid[0], list):
        return _rot_list(grid)

    if isinstance(grid, dict):
        xs = [int(p.real) for p in grid.keys()]
        ys = [int(p.imag) for p in grid.keys()]
        min_x, max_x = min(xs), max(xs)
        min_y, max_y = min(ys), max(ys)
        n_rows = max_x - min_x + 1
        n_cols = max_y - min_y + 1

        grid_new = {}
        for c in range(0, n_cols, 2):
            dst_r = c // 2
            dst_c = n_cols - 1 - c // 2

            for r in range(n_rows):
                a = r + c
                if a < n_cols:
                    src_pos = (r + min_x) + (a + min_y) * 1j
                    if src_pos in grid and grid[src_pos] != ".":
                        dst_pos = (dst_r + min_x) + (dst_c + min_y) * 1j
                        grid_new[dst_pos] = grid[src_pos]
                        dst_c -= 1

                b = a + 1
                if b < n_cols:
                    src_pos = (r + min_x) + (b + min_y) * 1j
                    if src_pos in grid and grid[src_pos] != ".":
                        dst_pos = (dst_r + min_x) + (dst_c + min_y) * 1j
                        grid_new[dst_pos] = grid[src_pos]
                        dst_c -= 1

        return grid_new

    return None

def bfs(src, graph, level):
    from collections import deque
    dist = {(src, level): 0}
    q = deque([(src, level)])

    while q:
        node, level = q.popleft()
        if graph[level][node] == "E":
            return dist[(node, level)]
        
        dir_options = [0, -1, 1j, -1j] if (node.real + node.imag) % 2 == 0 else [0, 1, 1j, -1j]
        for dir in dir_options:
            neighbor = node + dir
            if neighbor in graph[(level + 1) % 3] and graph[(level + 1) % 3][neighbor] in "TE" and (neighbor, (level + 1) % 3) not in dist:
                dist[(neighbor, (level + 1) % 3)] = dist[(node, level)] + 1
                q.append((neighbor, (level + 1) % 3))

    return -1

graph1 = graph.copy()
graph2 = rotate(graph1)
graph3 = rotate(graph2)
graphs = [graph1, graph2, graph3]
print(bfs(start, graphs, 0))