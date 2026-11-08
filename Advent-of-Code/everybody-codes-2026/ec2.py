import re
from graphlib import TopologicalSorter

total = 0
for line in open("../input.txt").read().splitlines():
    g = {}
    for a, op, b in re.findall(r"(\d+)([<>])(\d+)", line):
        hi, lo = (a, b) if op == ">" else (b, a)
        g.setdefault(lo, set()).add(hi)  # harder alloy comes first
    total += int("".join(TopologicalSorter(g).static_order()))
print(total)
