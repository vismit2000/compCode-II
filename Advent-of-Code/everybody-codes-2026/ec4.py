import re
from collections import defaultdict

recs = re.findall(r"id=(\d+) quest=(\d+) part=(\d+) time=(\d+)", open("../input.txt").read())

# Part I & II
stats = defaultdict(lambda: [0, 0])  # id -> [-parts, total time]
for pid, _, _, t in recs:
    stats[pid][0] -= 1  # negative so more parts sorts first
    stats[pid][1] += int(t)
print(sum(i * t for i, (_, t) in enumerate(sorted(stats.values()), 1)))

# Part III
time = {(q, pid, int(p)): int(t) for pid, q, p, t in recs}
quests = {q for q, _, _ in time}

score = defaultdict(int)
for q in quests:
    for p in (1, 2, 3):
        # combined time of parts 1..p, for everyone who finished part p
        combined = {pid: sum(time[q, pid, k] for k in range(1, p + 1))
                    for qq, pid, pp in time if qq == q and pp == p}
        for pid, t in combined.items():
            position = 1 + sum(other < t for other in combined.values())  # ties share a position
            score[pid] += max(0, 50 * p + 1 - position)

scores = score.values()
print(sum((1 + sum(other > s for other in scores)) * s for s in scores))
