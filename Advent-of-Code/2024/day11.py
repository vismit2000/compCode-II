with open("input.txt", "r") as file:
    lines = file.read().strip().split("\n")
    stones_list = tuple(map(int, lines[0].split(" ")))
    stones = {}
    for stone in stones_list:
        stones[stone] = stones.get(stone, 0) + 1


def rule(stone):
    stone_str = str(stone)
    if stone == 0:
        return [1]
    if len(stone_str) % 2 == 0:
        half = len(stone_str) // 2
        return [int(stone_str[:half]), int(stone_str[half:])]
    return [2024 * stone]


def transform_stones(stones):
    updated_stones = {}
    for stone in stones:
        for new_stone in rule(stone):
            updated_stones[new_stone] = updated_stones.get(new_stone, 0) + stones[stone]
    return updated_stones


for i in range(75):
    stones = transform_stones(stones)
    if i == 24:
        print(sum(stones.values()))
print(sum(stones.values()))