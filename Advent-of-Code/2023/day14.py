content = open("input.txt", "r").read()
lines = content.split("\n")

lines = tuple(["".join(row) for row in zip(*lines)][::-1])  # rotate anticlockwise


def tilt(grid):
    matrix = [["." for _ in range(len(grid))] for _ in range(len(grid[0]))]
    for i, line in enumerate(grid):
        pos_avl = 0
        for pos, ch in enumerate(line):
            if ch == "#":
                pos_avl = pos + 1
                matrix[i][pos] = "#"
            elif ch == "O":
                matrix[i][pos_avl] = "O"
                pos_avl += 1
    return tuple(["".join(row) for row in matrix])


def load(grid) -> int:
    grid = ["".join(row[::-1]) for row in zip(*grid)]  # rotate clockwise
    return sum([row.count("O") * (len(grid) - i) for i, row in enumerate(grid)])


# Part 1
print(f"Part 1: {load(tilt(lines))}")

# Part 2 (Cycle detection)
N = 1_000_000_000
cache = {lines: 0}
i = 1
result_matrix = ()
while i <= N:
    for rep in range(4):
        lines = tilt(lines)
        lines = tuple(["".join(row[::-1]) for row in zip(*lines)])  # rotate clockwise
    if lines not in cache:
        cache[lines] = i
    else:
        cycle_len = i - cache[lines]
        idx = cache[lines] + (N - cache[lines]) % cycle_len
        for k, v in cache.items():
            if v == idx:
                result_matrix = k
                break
    if result_matrix:
        break
    i += 1

print(f"Part 2: {load(result_matrix)}")
