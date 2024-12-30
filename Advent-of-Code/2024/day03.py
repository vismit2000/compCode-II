import re


def extract_and_multiply(memory):
    total_sum1, total_sum2 = 0, 0
    enabled = True

    for match in re.findall(r"(do\(\)|don\'t\(\)|mul\(\d{1,3},\d{1,3}\))", memory):
        if match == "do()":
            enabled = True
        elif match == "don't()":
            enabled = False
        else:
            x, y = map(int, re.findall(r"\d{1,3}", match))
            total_sum1 += x * y
            total_sum2 += x * y if enabled else 0

    return total_sum1, total_sum2


memory = open("input.txt", "r").read().strip()
print(extract_and_multiply(memory))