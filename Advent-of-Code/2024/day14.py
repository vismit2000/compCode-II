import re
from math import prod
from statistics import mean

with open("input.txt", "r") as file:
    lines = file.read().strip().split("\n")
    robots = [tuple(map(int, re.findall(r"-?\d+", line))) for line in lines]
    Xs = [x for x, y, _, _ in robots]
    Ys = [y for x, y, _, _ in robots]
    width = max(Xs) + 1
    height = max(Ys) + 1


def robot_dance(robots, steps=100) -> list:
    return [
        ((x + steps * dx) % width, (y + steps * dy) % height)
        for (x, y, dx, dy) in robots
    ]


d = {}
points = robot_dance(robots)
for posx, posy in points:
    if posx == width // 2 or posy == height // 2:
        continue
    qx = 0 if posx < width // 2 else 1
    qy = 0 if posy < height // 2 else 1
    d[(qx, qy)] = d.get((qx, qy), 0) + 1

print(prod(d.values()))


def mean_distance_to_centroid(points) -> float:
    """The mean of each point's distance to the centroid."""
    centroid = (mean(point[0] for point in points), mean(point[1] for point in points))
    return mean(abs(p[0] - centroid[0]) + abs(p[1] - centroid[1]) for p in points)


def most_clustered_time(robots, times=range(10_000)) -> int:
    """Out of all the time steps, the one that has the robots the most clustered together."""
    return min(times, key=lambda t: mean_distance_to_centroid(robot_dance(robots, t)))


t = most_clustered_time(robots)
print(t)