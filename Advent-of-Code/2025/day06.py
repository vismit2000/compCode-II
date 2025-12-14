import operator
from itertools import groupby
from functools import reduce

with open("input.txt") as f:
    lines = f.read().strip().split("\n")

ops = {"+": operator.add, "*": operator.mul}

# Part 1: Process rows, apply operators from last row
rows = [list(map(int, line.split())) for line in lines[:-1]] + [lines[-1].split()]
print(sum(reduce(ops[col[-1]], col[:-1]) for col in zip(*rows)))

# Part 2: Process columns, extract vertical numbers and operators
grid = list(zip(*[line.ljust(max(len(l) for l in lines)) for line in lines]))
operators = [line[-1] for line in grid if line[-1] in ops]
nums = ["".join(line[:-1]).strip() for line in grid]
groups = [[int(n) for n in list(g)] for k, g in groupby(nums, bool) if k]
print(sum(reduce(ops[op], grp) for op, grp in zip(operators, groups)))