with open("input.txt", "r") as file:
    world = file.read().strip().split("\n")
    world = [list(line) for line in world]
    n, m = len(world), len(world[0])

Point = complex

start = next(Point(i, j) for i in range(n) for j in range(m) if world[i][j] == "^")


def simulate(world, start):
    pos = start
    heading = Point(-1, 0)
    visited = set()
    while True:
        visited.add((int(pos.real), int(pos.imag)))
        next_pos = pos + heading
        if (
            next_pos.real < 0
            or next_pos.imag < 0
            or next_pos.real >= n
            or next_pos.imag >= m
        ):
            break
        if world[int(next_pos.real)][int(next_pos.imag)] == "#":
            heading *= Point(0, -1)
        else:
            pos += heading
    return visited


def loop(world, start):
    pos = start
    heading = Point(-1, 0)
    visited = set()
    while True:
        visited.add((pos, heading))
        next_pos = pos + heading
        if (
            next_pos.real < 0
            or next_pos.imag < 0
            or next_pos.real >= n
            or next_pos.imag >= m
        ):
            return False
        if world[int(next_pos.real)][int(next_pos.imag)] == "#":
            heading *= Point(0, -1)
        else:
            pos += heading

        if (pos, heading) in visited:
            return True


visited = simulate(world, start)
print(len(visited))

cnt = 0
for i, j in visited - {(int(start.real), int(start.imag))}:
    world[i][j] = "#"
    if loop(world, start):
        cnt += 1
    world[i][j] = "."
print(cnt)


# G = {
#     i + j * 1j: c
#     for i, r in enumerate(open("input.txt"))
#     for j, c in enumerate(r.strip())
# }
# start = min(p for p in G if G[p] == "^")


# def walk(G):
#     pos, dir, seen = start, -1, set()
#     while pos in G and (pos, dir) not in seen:
#         seen |= {(pos, dir)}
#         if G.get(pos + dir) == "#":
#             dir *= -1j
#         else:
#             pos += dir
#     return {p for p, _ in seen}, (pos, dir) in seen


# path = walk(G)[0]
# print(len(path), sum(walk(G | {o: "#"})[1] for o in path))