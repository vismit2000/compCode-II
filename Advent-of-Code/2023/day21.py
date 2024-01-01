# Only solved part 1 :(

content = open("input.txt", "r").read()
lines = content.split("\n")
n, m = len(lines), len(lines[0])

s = set()
for i in range(n):
    for j in range(m):
        if lines[i][j] == "S":
            s.add((i, j))

for _ in range(64):
    new_s = set()
    for i, j in s:
        for di, dj in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
            if lines[(i + di) % n][(j + dj) % m] != "#":
                new_s.add((i + di, j + dj))
    s = new_s
print(len(s))
