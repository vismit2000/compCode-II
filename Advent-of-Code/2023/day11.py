content = open("input.txt", "r").read()
lines = content.split("\n")
n, m = len(lines), len(lines[0])
factor = 1000000

xs, ys = [], []
x, y = 0, 0
for i in range(n):
    xs.append(x)
    x += factor if "#" not in lines[i] else 1
for j in range(m):
    ys.append(y)
    y += factor if "#" not in [row[j] for row in lines] else 1

coords = [(xs[i], ys[j]) for i in range(n) for j in range(m) if lines[i][j] == "#"]

from itertools import combinations

ans = 0
for comb in list(combinations(coords, 2)):
    ans += abs(comb[0][0] - comb[1][0]) + abs(comb[0][1] - comb[1][1])
print(ans)
