content = open("input.txt", "r").read()
lines = content.split("\n")

instr = lines[0]
n = len(instr)

d = {}

for line in lines[2:]:
    node, edges = line.split(" = ")
    left, right = edges[1:-1].split(", ")
    d[node] = (left, right)

curr = []
for key in d:
    if key.endswith("A"):
        curr.append(key)

steps = []
for c in curr:
    step = 0
    while not c.endswith("Z"):
        dir = 0 if instr[step % n] == "L" else 1
        c = d[c][dir]
        step += 1
    steps.append(step)

from math import lcm

print(lcm(*steps))
