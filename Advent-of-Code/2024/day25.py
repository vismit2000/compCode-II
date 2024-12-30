with open("input.txt", "r") as file:
    lines = file.read().strip().split("\n\n")
    grids = [list(zip(*block.splitlines())) for block in lines]
    counts = [[row.count("#") - 1 for row in grid] for grid in grids]
    locks = [count for count, grid in zip(counts, grids) if grid[0][0] == "#"]
    keys = [count for count, grid in zip(counts, grids) if grid[0][0] == "."]

total = 0
for key in keys:
    for lock in locks:
        if all(x + y <= 5 for x, y in zip(key, lock)):
            total += 1
print(total)