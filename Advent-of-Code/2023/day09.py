# Mathologer video on what comes next sequence: https://www.youtube.com/watch?v=4AuV93LOPcE

from math import comb

content = open("input.txt", "r").read()
lines = content.split("\n")

series = [[int(num) for num in line.split()] for line in lines]
next = []
for seq in series:
    seq = seq[::-1]
    n = len(seq)
    diffs = [seq]
    while not all(ele == 0 for ele in seq):
        seq = [seq[i + 1] - seq[i] for i in range(len(seq) - 1)]
        diffs.append(seq)
    ans = 0
    for i in range(len(diffs)):
        ans += diffs[i][0] * comb(n, i)
    next.append(ans)
print(sum(next))
