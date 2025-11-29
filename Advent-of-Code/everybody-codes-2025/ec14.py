# cycle detection

from frozendict import frozendict

with open("input.txt", "r") as file:
    lines = file.read().strip().split("\n")
    pattern = {i + j * 1j: c for i, r in enumerate(lines) for j, c in enumerate(r)}
    grid = {i + j * 1j: "." for i in range(34) for j in range(34)}
    T = 1_000_000_000

def match_pattern(grid, pattern):
    return all(grid[pos + 13 + 13j] == state for pos, state in pattern.items())

def step(grid):
    new_grid = {}
    for point, state in grid.items():
        active_neighbors = sum(
            grid.get(point + delta, ".") == "#"
            for delta in [-1 - 1j, 1 - 1j, -1 + 1j, 1 + 1j]
        )
        new_grid[point] = "."
        if state == "#" and active_neighbors % 2 == 1 or state == "." and active_neighbors % 2 == 0:
            new_grid[point] = "#"
    return new_grid

seen = set()
seq = []
while True:
    grid = step(grid)
    if frozendict(grid) in seen:
        break
    seen.add(frozendict(grid))
    seq.append(frozendict(grid))

cycle_start = seq.index(frozendict(grid))
cycle_len = len(seq) - cycle_start
print(f"Cycle detected: starts at {cycle_start}, length {cycle_len}")

total_active = 0
for grid in seq[cycle_start:]:
    if match_pattern(grid, pattern):
        total_active += sum(1 for state in grid.values() if state == "#")
total_active *= (T - cycle_start) // cycle_len

for grid in seq[:cycle_start]:
    if match_pattern(grid, pattern):
        total_active += sum(1 for state in grid.values() if state == "#")

for grid in seq[cycle_start:][:(T - cycle_start) % cycle_len]:
    if match_pattern(grid, pattern):
        total_active += sum(1 for state in grid.values() if state == "#")
print(total_active)