import re

with open("input.txt") as f:
    lines = f.read().strip().split("\n\n")[-1].splitlines()

total = 0
for line in lines:
    x, y, *counts = list(map(int, re.findall(r"\d+", line)))
    total += (x//3) * (y // 3) >= sum(counts)
print(total)