content = open("input.txt", "r").read()
lines = content.split("\n")
n, m = len(lines), len(lines[0])

bricks = []
xmax, ymax = 0, 0

for line in lines:
    first, second = line.split("~")
    first = tuple(map(int, first.split(",")))
    second = tuple(map(int, second.split(",")))

    if first[2] > second[2]:
        first, second = second, first
    bricks.append((first, second))

    xmax = max([xmax, first[0], second[0]])
    ymax = max([ymax, first[1], second[1]])

bricks.sort(key=lambda x: x[1][2])

graph = {i: {"forward": set(), "backward": set()} for i in range(n)}
zc_occupied = [[(0, -1) for _ in range(ymax + 1)] for _ in range(xmax + 1)]


def count_brick_falls(graph, k):
    in_deg = {k: len(v["backward"]) for k, v in graph.items()}
    count = -1
    q = [k]
    while q:
        node = q.pop()
        count += 1
        for child in graph[node]["forward"]:
            in_deg[child] -= 1
            if in_deg[child] == 0:
                q.append(child)
    return count


for bid, brick in enumerate(bricks):
    maxz = max(
        [
            zc_occupied[i][j][0]
            for i in range(brick[0][0], brick[1][0] + 1)
            for j in range(brick[0][1], brick[1][1] + 1)
        ]
    )
    for i in range(brick[0][0], brick[1][0] + 1):
        for j in range(brick[0][1], brick[1][1] + 1):
            if zc_occupied[i][j][1] != -1 and zc_occupied[i][j][0] == maxz:
                graph[zc_occupied[i][j][1]]["forward"].add(bid)
                graph[bid]["backward"].add(zc_occupied[i][j][1])
            zc_occupied[i][j] = (maxz + brick[1][2] - brick[0][2] + 1, bid)

part_1_ans, part_2_ans = 0, 0
for k, v in graph.items():
    if all([len(graph[node]["backward"]) > 1 for node in v["forward"]]):
        part_1_ans += 1
    else:
        part_2_ans += count_brick_falls(graph, k)

print(part_1_ans, part_2_ans)
