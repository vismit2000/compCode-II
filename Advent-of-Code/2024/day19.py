from functools import lru_cache

with open("input.txt", "r") as file:
    lines = file.read().strip().split("\n")
    patterns = set(lines[0].split(", "))


@lru_cache(maxsize=None)
def num_ways(design):
    if design == "":
        return 1
    return sum(
        num_ways(design[len(pattern) :])
        for pattern in patterns
        if design.startswith(pattern)
    )


print(sum(1 for line in lines[2:] if num_ways(line) > 0))
print(sum(num_ways(line) for line in lines[2:]))