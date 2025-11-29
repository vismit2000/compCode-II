import heapq
from collections import defaultdict

with open("input.txt") as f:
    lines = f.read().strip().split("\n")
    segments = [tuple(map(int, line.split(","))) for line in lines]
    segments.sort()
    WIDTH = max(segment[0] for segment in segments)
    HEIGHT = max(segment[1] + segment[2] for segment in segments)
    openings = defaultdict(list)
    for x, y, length in segments:
        openings[x].append((y, y + length))
    default_open = (0, HEIGHT + 1)  # treat missing columns as a full opening

def valid_move(node, neighbor, openings):
    if neighbor.real < 0 or neighbor.imag < 0 or neighbor.real > HEIGHT or neighbor.imag > WIDTH:
        return False

    def has_open(x_coord, y_val):
        intervals = openings.get(int(x_coord), [default_open])
        return any(start <= y_val < end for start, end in intervals)

    return has_open(node.imag, node.real) and has_open(neighbor.imag, neighbor.real)

def dijkstra(start):
    # Compressed Dijkstra: we keep only the x coordinates that were specified in input
    # (plus 0 and WIDTH) and jump across runs of default/full columns.
    # Nodes are (x, y) tuples where x and y are ints.
    xs = sorted(set(openings.keys()) | {0, WIDTH})
    pos2idx = {x: i for i, x in enumerate(xs)}

    def neighbors(x, y):
        i = pos2idx[x]
        if i == len(xs) - 1:
            return []
        nx = xs[i + 1]
        gap = nx - x
        nxt_intervals = openings.get(nx, [default_open])
        res = []

        # possible y' at nx must be within [y-gap, y+gap] AND inside an interval at nx
        # parity constraint: (gap + (y' - y)) must be even for y' to be reachable
        parity_target = (y + gap) & 1

        for (b0, b1) in nxt_intervals:
            low = max(b0, y - gap)
            high = min(b1 - 1, y + gap)
            if low > high:
                continue

            # Choose candidate y' near the low boundary (minimizes number of down moves)
            y1 = low if (low & 1) == parity_target else low + 1
            if y1 <= high:
                # cost (#down moves) for fixed y->y1 across gap steps
                down_moves = (gap + (y1 - y)) // 2
                if 0 <= down_moves <= gap:
                    res.append((nx, y1, down_moves))

            # also consider a candidate near the high boundary (may be needed downstream)
            y2 = high if (high & 1) == parity_target else high - 1
            if y2 >= low and y2 != y1:
                down_moves2 = (gap + (y2 - y)) // 2
                if 0 <= down_moves2 <= gap:
                    res.append((nx, y2, down_moves2))

        return res

    dist = {(0, start): 0}
    pq = [(0, (0, start))]

    while pq:
        d, (x, y) = heapq.heappop(pq)
        if d != dist.get((x, y), float('inf')):
            continue

        for nx, ny, cost in neighbors(x, y):
            nd = d + cost
            key = (nx, ny)
            if nd < dist.get(key, float('inf')):
                dist[key] = nd
                heapq.heappush(pq, (nd, key))

    return dist

dist = dijkstra(0)
print(min([d for (x, _), d in dist.items() if x == WIDTH]))