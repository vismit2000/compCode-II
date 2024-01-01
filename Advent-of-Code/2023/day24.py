# Topcoder geometry - part 2: https://www.topcoder.com/community/competitive-programming/tutorials/geometry-concepts-line-intersection-and-its-applications/

from itertools import combinations

content = open("input.txt", "r").read()
lines = content.split("\n")
n, m = len(lines), len(lines[0])

low, high = 200000000000000, 400000000000000


def check_intersection(p1, v1, p2, v2):
    x1, y1 = p1
    x2, y2 = p1[0] + v1[0], p1[1] + v1[1]
    A1, B1, C1 = y2 - y1, x1 - x2, x1 * y2 - x2 * y1

    x1, y1 = p2
    x2, y2 = p2[0] + v2[0], p2[1] + v2[1]
    A2, B2, C2 = y2 - y1, x1 - x2, x1 * y2 - x2 * y1

    det = A1 * B2 - A2 * B1
    if det == 0:
        return (-1, -1)
    return ((B2 * C1 - B1 * C2) / det, (A1 * C2 - A2 * C1) / det)


points, velocities = [], []
for line in lines:
    point, velocity = line.split(" @ ")
    points.append(tuple(map(int, point.split(", "))))
    velocities.append(tuple(map(int, velocity.split(", "))))

ans = 0
for hs1, hs2 in combinations(range(n), 2):
    x, y = check_intersection(
        points[hs1][:-1], velocities[hs1][:-1], points[hs2][:-1], velocities[hs2][:-1]
    )
    times = (
        (x - points[hs1][0]) / velocities[hs1][0],
        (x - points[hs2][0]) / velocities[hs2][0],
        (y - points[hs1][1]) / velocities[hs1][1],
        (y - points[hs2][1]) / velocities[hs2][1],
    )
    if low <= x <= high and low <= y <= high and all(tim > 0 for tim in times):
        ans += 1

print(ans)
