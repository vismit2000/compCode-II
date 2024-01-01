content = open("input.txt", "r").read()
lines = content.split("\n")
n, m = len(lines), len(lines[0])

# L -> 0, D -> 1, R -> 2, U -> 3
opp = [2, 3, 0, 1]
dx = [0, 1, 0, -1]
dy = [-1, 0, 1, 0]
dirs = {
    "/": [(3,), (2,), (1,), (0,)],
    "\\": [(1,), (0,), (3,), (2,)],
    "|": [(1, 3), (3,), (1, 3), (1,)],
    "-": [(2,), (0, 2), (0,), (0, 2)],
    ".": [(2,), (3,), (0,), (1,)],
}


def energize(startx, starty, startdir):
    queue = [(startx, starty, startdir)]
    visited = {(startx, starty, startdir)}

    while queue:
        x, y, d = queue.pop(0)
        for dir in dirs[lines[x][y]][d]:
            nx, ny = x + dx[dir], y + dy[dir]
            if nx < 0 or nx >= n or ny < 0 or ny >= m or (nx, ny, opp[dir]) in visited:
                continue
            queue.append((nx, ny, opp[dir]))
            visited.add((nx, ny, opp[dir]))

    return len({(i, j) for i, j, _ in visited})


part2 = 0
for i in range(n):
    part2 = max([part2, energize(i, 0, 0), energize(i, m - 1, 2)])
for j in range(m):
    part2 = max([part2, energize(0, j, 3), energize(n - 1, j, 1)])
print(energize(0, 0, 0), part2)
