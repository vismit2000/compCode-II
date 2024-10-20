# https://adventofcode.com/2018/day/22
# Standard Dijkstra (using networkx)

import re
import heapq
from enum import IntEnum

import networkx as nx

content = open("input.txt", "r").read()
lines = content.split("\n")

depth = tuple(map(int, re.findall(r"-?\d+", lines[0])))[0]
target = tuple(map(int, re.findall(r"-?\d+", lines[1])))


class Terrain(IntEnum):
    ROCKY = 0
    WET = 1
    NARROW = 2


class Equipment(IntEnum):
    TORCH = 0
    GEAR = 1
    NEITHER = 2


valid_equipments = {
    Terrain.ROCKY: {Equipment.TORCH, Equipment.GEAR},
    Terrain.WET: {Equipment.GEAR, Equipment.NEITHER},
    Terrain.NARROW: {Equipment.TORCH, Equipment.NEITHER},
}


def generate_grid(depth, target, corner):
    grid = []
    for y in range(corner[1] + 1):
        row = []
        for x in range(corner[0] + 1):
            if (x, y) == (0, 0) or (x, y) == target:
                geo_index = 0
            elif y == 0:
                geo_index = x * 16807
            elif x == 0:
                geo_index = y * 48271
            else:
                geo_index = row[x - 1][0] * grid[y - 1][x][0]
            erosion_level = (geo_index + depth) % 20183
            terrain = erosion_level % 3
            row.append((erosion_level, terrain))
        grid.append(row)
    return grid


def dijksktra(grid, target):
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    visited = set()
    heap = [(0, (0, 0), Equipment.TORCH)]
    while heap:
        time, (x, y), equipment = heapq.heappop(heap)
        if (x, y, equipment) in visited:
            continue
        visited.add((x, y, equipment))
        if (x, y) == target and equipment == Equipment.TORCH:
            return time

        # Change equipment
        equipments = valid_equipments[grid[y][x][1]]
        other_equipment = (equipments - {equipment}).pop()
        heapq.heappush(heap, (time + 7, (x, y), other_equipment))

        # Move to adjacent cells
        for dx, dy in directions:
            new_x, new_y = x + dx, y + dy
            if new_x < 0 or new_y < 0 or new_x >= len(grid[0]) or new_y >= len(grid):
                continue
            if equipment in valid_equipments[grid[new_y][new_x][1]]:
                heapq.heappush(heap, (time + 1, (new_x, new_y), equipment))

    return -1  # If no path is found


def dijkstra_nx(grid, target):
    graph = nx.Graph()
    for y in range(len(grid)):
        for x in range(len(grid[0])):
            equipments = valid_equipments[grid[y][x][1]]
            first, second = equipments
            graph.add_edge((x, y, first), (x, y, second), weight=7)
            for dx, dy in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
                new_x, new_y = x + dx, y + dy
                if (
                    new_x < 0
                    or new_y < 0
                    or new_x >= len(grid[0])
                    or new_y >= len(grid)
                ):
                    continue
                new_equipments = valid_equipments[grid[new_y][new_x][1]]
                for equipment in new_equipments & equipments:
                    graph.add_edge(
                        (x, y, equipment), (new_x, new_y, equipment), weight=1
                    )

    return nx.dijkstra_path_length(
        graph, (0, 0, Equipment.TORCH), (target[0], target[1], Equipment.TORCH)
    )


corner = target
grid = generate_grid(depth, target, corner)
print(sum(sum(cell[1] for cell in row) for row in grid))
corner = tuple(map(lambda x: x + 100, target))
grid = generate_grid(depth, target, corner)
print(dijksktra(grid, target))
print(dijkstra_nx(grid, target))
