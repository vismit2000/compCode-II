with open("input.txt") as f:
    lines = f.read().strip().split("\n")
    instructions = [(line[0], int(line[1:])) for line in lines]

dial, zeros = 50, 0
for action, value in instructions:
    zeros += value // 100
    value = value % 100
    for _ in range(value):
        dial = (dial - 1) % 100 if action == "L" else (dial + 1) % 100
        zeros += dial == 0

print(zeros)