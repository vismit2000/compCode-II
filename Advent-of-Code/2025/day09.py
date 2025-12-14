from itertools import combinations
from shapely import Polygon, box

with open("input.txt") as f:
    lines = f.read().strip().split("\n")
    points = [tuple(map(int, line.split(","))) for line in lines]

def convex_hull(points):
    # points: list of (x, y)
    points = sorted(set(points))
    if len(points) <= 1:
        return points

    def cross(o, a, b):
        # cross product (OA x OB)
        return (a[0] - o[0]) * (b[1] - o[1]) - \
               (a[1] - o[1]) * (b[0] - o[0])

    lower = []
    for p in points:
        while len(lower) >= 2 and cross(lower[-2], lower[-1], p) <= 0:
            lower.pop()
        lower.append(p)

    upper = []
    for p in reversed(points):
        while len(upper) >= 2 and cross(upper[-2], upper[-1], p) <= 0:
            upper.pop()
        upper.append(p)

    # last point of each list is start of the other list
    return lower[:-1] + upper[:-1]

hull = convex_hull(points)
# print(hull)
# print(max((a[0] - b[0] + 1) * (a[1] - b[1] + 1) for a, b in combinations(points, 2)))

poly = Polygon(points)
answer1 = answer2 = 0
for (x1, y1), (x2, y2) in combinations(points, 2):
    rect_size = (abs(x1 - x2) + 1) * (abs(y1 - y2) + 1)
    answer1 = max(answer1, rect_size)
    if rect_size < answer2:
        continue
    rect = box(min(x1, x2), min(y1, y2), max(x1, x2), max(y1, y2))
    if poly.contains(rect):
        answer2 = max(answer2, rect_size)

print(answer1, answer2)