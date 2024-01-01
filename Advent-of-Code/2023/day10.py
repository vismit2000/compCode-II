import sys

sys.setrecursionlimit(1000000)

content = open("input.txt", "r").read()
lines = content.split("\n")
n, m = len(lines), len(lines[0])


def floodfill(grid, x, y, c):
    if x < 0 or x >= len(grid) or y < 0 or y >= len(grid[0]) or grid[x][y] != 0:
        return
    grid[x][y] = c
    floodfill(grid, x + 1, y, c)
    floodfill(grid, x - 1, y, c)
    floodfill(grid, x, y + 1, c)
    floodfill(grid, x, y - 1, c)


pipes = "|-LJ7F"
dirs = [
    [(-1, 0), (1, 0)],
    [(0, -1), (0, 1)],
    [(-1, 0), (0, 1)],
    [(-1, 0), (0, -1)],
    [(0, -1), (1, 0)],
    [(1, 0), (0, 1)],
]

x_s, y_s = -1, -1
for i in range(n):
    for j in range(m):
        if lines[i][j] == "S":
            x_s, y_s = i, j
            break

lines[x_s] = lines[x_s][:y_s] + "7" + lines[x_s][y_s + 1 :]

queue = []
queue.append((x_s, y_s, 0, (0, 0)))
dist = [[1000000 for _ in range(m)] for _ in range(n)]
grid = [[0 for _ in range(2 * m + 2)] for _ in range(2 * n + 2)]

while len(queue) > 0:
    x, y, d, dr = queue.pop(0)
    dist[x][y] = d
    grid[2 * x + 1][2 * y + 1] = 1
    grid[2 * x + 1 - dr[0]][2 * y + 1 - dr[1]] = 1
    if lines[x][y] in pipes:
        for dir in dirs[pipes.index(lines[x][y])]:
            x1, y1 = x + dir[0], y + dir[1]
            if x1 >= 0 and x1 < n and y1 >= 0 and y1 < m and dist[x1][y1] >= dist[x][y]:
                queue.append((x1, y1, d + 1, dir))

floodfill(grid, len(grid) - 1, len(grid[0]) - 1, 2)

area, farthest = 0, 0
for i in range(n):
    for j in range(m):
        if grid[2 * i + 1][2 * j + 1] == 0:
            area += 1
        if dist[i][j] < 1000000:
            farthest = max(farthest, dist[i][j])
print(farthest, area)
