content = open("input.txt", "r").read()
lines = content.split("\n")

import math

times = [int(tim) for tim in lines[0].split(":")[1].split()]
distances = [int(dist) for dist in lines[1].split(":")[1].split()]


def calc(T, D):
    if T * T - 4 * D < 0:
        return 0
    end = (T + math.sqrt(T * T - 4 * D)) / 2
    start = (T - math.sqrt(T * T - 4 * D)) / 2
    if end.is_integer():
        end -= 1
    if start.is_integer():
        start += 1
    return math.floor(end) - math.ceil(start) + 1


ans = 1
for T, D in zip(times, distances):
    ans *= calc(T, D)
print(ans)

T = int("".join([str(t) for t in times]))
D = int("".join([str(d) for d in distances]))

print(calc(T, D))
