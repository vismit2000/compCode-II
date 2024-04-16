# Simulation on grid with a stopping condition

content = open("input.txt", "r").read()
grid = content.splitlines()
h, w = len(grid), len(grid[0])

east = {(i, j) for i in range(h) for j in range(w) if grid[i][j] == ">"}
south = {(i, j) for i in range(h) for j in range(w) if grid[i][j] == "v"}


def move_herd(herd: set[tuple[int, int]], other_herd, dx, dy) -> set[tuple[int, int]]:
    new_location = set()
    for x, y in herd:
        p = ((x + dx) % h, (y + dy) % w)
        if p not in herd and p not in other_herd:
            new_location.add(p)
        else:
            new_location.add((x, y))
    return new_location


step = 0
while True:
    step += 1
    new_east = move_herd(east, south, 0, 1)
    new_south = move_herd(south, new_east, 1, 0)

    if east == new_east and south == new_south:
        break

    east, south = new_east, new_south

print(step)
