# Conway Cubes - Game of Life in 3-D (or n-D)

from itertools import chain

flatten = chain.from_iterable

content = open("input.txt", "r").read()
grid = content.splitlines()


def neighborhood(point) -> list[tuple]:
    x, y, z, w = point
    return [
        (x + i, y + j, z + k, w + l)
        for i in (-1, 0, 1)
        for j in (-1, 0, 1)
        for k in (-1, 0, 1)
        for l in (-1, 0, 1)
        if not all((i == 0, j == 0, k == 0, l == 0))
    ]


def next_generation(cubes) -> set[tuple]:
    candidates = set(flatten(map(neighborhood, cubes))) | cubes
    new_cubes = set()
    for point in candidates:
        active = sum((neighbor in cubes) for neighbor in neighborhood(point))
        if (point in cubes and active in (2, 3)) or (
            point not in cubes and active == 3
        ):
            new_cubes.add(point)
    return new_cubes


def simulate(cubes, n=6) -> set[tuple]:
    for gen in range(n):
        cubes = next_generation(cubes)
    return cubes


cubes = {
    (i, j, 0, 0)
    for i in range(len(grid))
    for j in range(len(grid[0]))
    if grid[i][j] == "#"
}


print(len(simulate(cubes)))


# # pytudes (n-D arbitrary sized Game of Life)
# import operator
# from functools import lru_cache
# from itertools import product
# from collections import Counter

# Cell = tuple[int, ...]


# def day17_1(picture, d=3, n=6):
#     "How many cells are active in the nth generation?"
#     return len(life(parse_cells(picture, d), n))


# def parse_cells(picture, d=3, active="#") -> set[Cell]:
#     "Convert a 2-d picture into a set of d-dimensional active cells."
#     return {
#         (x, y, *(0,) * (d - 2))
#         for (y, row) in enumerate(picture)
#         for x, cell in enumerate(row)
#         if cell is active
#     }


# def life(cells, n) -> set[Cell]:
#     "Play n generations of Life."
#     for g in range(n):
#         cells = next_generation(cells)
#     return cells


# def next_generation(cells) -> set[Cell]:
#     """The set of live cells in the next generation."""
#     return {
#         cell
#         for cell, count in neighbor_counts(cells).items()
#         if count == 3 or (count == 2 and cell in cells)
#     }


# @lru_cache()
# def cell_deltas(d: int):
#     return set(filter(any, product((-1, 0, +1), repeat=d)))


# def neighbor_counts(cells) -> dict[Cell, int]:
#     """A Counter of the number of live neighbors for each cell."""
#     return Counter(flatten(map(neighbors, cells)))


# def neighbors(cell) -> list[Cell]:
#     "All adjacent neighbors of cell in three dimensions."
#     return [tuple(map(operator.add, cell, delta)) for delta in cell_deltas(len(cell))]
