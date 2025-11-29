from itertools import combinations
with open("input.txt") as f:
    data = f.read()
    nails = [int(x) for x in data.split(",")]
    SLOTS = 256
# print(sum(abs(n1 - n2) == SLOTS//2 for n1, n2 in zip(nails, nails[1:])))

def cut(s1, s2):
    points = sorted([s1[0], s1[1], s2[0], s2[1]])
    return len(set(points)) != 3 and ((points[0] in s1 and points[2] in s1) or (points[1] in s1 and points[3] in s1))
    

# strings = [(n1, n2) for n1, n2 in zip(nails, nails[1:])]
# max_cuts = 0
# for n1, n2 in combinations(range(1, SLOTS+1), 2):
#     current_cuts = sum(cut((n1, n2), s) for s in strings)
#     max_cuts = max(max_cuts, current_cuts)
#     # print(f"Checking ({n1}, {n2}): {current_cuts} cuts")
# # knots = sum(cut(s1, s2) for s1, s2 in combinations(strings, 2))
# print(max_cuts)

from collections import defaultdict
links = defaultdict(list)
for a, b in zip(nails, nails[1:]):
    links[a].append(b)
    links[b].append(a)

best_cuts = 0
for a in range(1, SLOTS+1):
    cuts = 0
    for b in range(a+2, SLOTS+1):
        cuts -= sum(1 for c in links[b] if a<c<b-1)
        cuts += sum(1 for c in links[b-1] if not a<=c<=b)
        best_cuts = max(best_cuts, cuts+(b in links[a]))
print("Part 3:", best_cuts)