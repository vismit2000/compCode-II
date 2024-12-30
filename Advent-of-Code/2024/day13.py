import re
import numpy as np

ADD = (0, 10000000000000)

with open("input.txt", "r") as file:
    lines = file.read().strip().split("\n")
    data = [
        (
            list(map(int, re.findall(r"\d+", lines[i]))),
            list(map(int, re.findall(r"\d+", lines[i + 1]))),
            list(map(int, re.findall(r"\d+", lines[i + 2]))),
        )
        for i in range(0, len(lines), 4)
    ]

for add in ADD:
    ans = 0
    for a_values, b_values, prize_values in data:
        matrix = np.array([a_values, b_values]).T
        inverse = np.linalg.inv(matrix)
        prize_vector = np.array([x + add for x in prize_values])
        presses = np.dot(inverse, prize_vector)
        result = np.dot(presses, [3, 1])

        first = a_values[0] * round(presses[0]) + b_values[0] * round(presses[1])
        second = a_values[1] * round(presses[0]) + b_values[1] * round(presses[1])

        if first != prize_values[0] + add or second != prize_values[1] + add:
            continue
        else:
            ans += round(result)

    print(ans)