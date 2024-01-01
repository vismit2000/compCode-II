content = open("input.txt", "r").read()
lines = content.split("\n")
m = len(lines[0])

import re
from collections import defaultdict

# nonsymbols = [str(i) for i in range(10)] + ["."]
d = defaultdict(list)

def check(i, j1, j2, num):
    flag = False

    if i > 0:
        for j in range(max(j1 - 1, 0), min(j2 + 1, m)):
            if lines[i-1][j] == "*":
                flag = True
                d[(i-1, j)].append(num)

    if i < len(lines) - 1:
        for j in range(max(j1 - 1, 0), min(j2 + 1, m)):
            if lines[i+1][j] == "*":
                flag = True
                d[(i+1, j)].append(num)

    if j1 > 0 and lines[i][j1 - 1] == "*":
        flag = True
        d[(i, j1 - 1)].append(num)
    if j2 < m and lines[i][j2] == "*":
        flag = True
        d[(i, j2)].append(num)

    return flag

ans = 0
for i, line in enumerate(lines):
    matches = [(match.group(), match.start()) for match in re.finditer(r"\d+", line)]
    for num, pos in matches:
        if check(i, pos, pos + len(num), int(num)):
            ans += int(num)

ans = 0
for k, v in d.items():
    if len(v) == 2:
        ans += v[0] * v[1]

print(ans)