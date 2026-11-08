import re
from heapq import heappop, heappush

plants = [
    tuple(map(int, re.findall(r"=(\d+)", line))) for line in open("../input.txt").read().splitlines()
]


def grow(g, limit, leaves=False):
    # Jump between split times instead of simulating every second.
    # A split at T leaves two halves (length g//2) that split at T + g//2 + 1
    # and a new branch (length 1) that splits at T + 2*(g//2).
    if limit <= 1:
        return 1  # 1 leaf / 1 element after the first second already
    h = g // 2
    pending, heap = {g: 1}, [g]  # split time -> number of splits
    t = size = splits = 0
    while True:
        T = heappop(heap)
        n = pending.pop(T)
        branches = 1 + 2 * splits  # each split turns 1 branch into 3
        if not leaves and size + branches * (T - t) >= limit:
            return t - (size - limit) // branches  # size limit hit before this split
        size += branches * (T - t) + n  # every branch grows, plus n new 1-long branches
        splits, t = splits + n, T
        if (1 + splits if leaves else size) >= limit:  # every split adds one leaf
            return T
        for dt, m in ((h + 1, 2 * n), (2 * h, n)):
            if T + dt not in pending:
                heappush(heap, T + dt)
            pending[T + dt] = pending.get(T + dt, 0) + m


# Part I
print(sum(grow(g, limit) for _, g, limit in plants))

# Part II & III: limit on leaves
print(sum(grow(g, limit, leaves=True) for _, g, limit in plants))
