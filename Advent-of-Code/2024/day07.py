import re

with open("input.txt", "r") as file:
    lines = file.read().strip().split("\n")
    equations = [tuple(map(int, re.findall("[0-9]+", line))) for line in lines]


def check_equation_true(eq, k):
    total_ops = len(eq) - 2
    for i in range(k**total_ops):
        value = eq[1]
        temp = i
        for j in range(total_ops):
            op = temp % k
            temp //= k
            if op == 0:
                value += eq[j + 2]
            elif op == 1:
                value *= eq[j + 2]
            elif op == 2:
                value = int(str(value) + str(eq[j + 2]))
            if value > eq[0]:
                break
        if value == eq[0]:
            return True
    return False


print(sum(eq[0] for eq in equations if check_equation_true(eq, 2)))
print(sum(eq[0] for eq in equations if check_equation_true(eq, 3)))


# def check_equation_true(eq):
#     total_ops = len(eq) - 2
#     for i in range(1 << total_ops):
#         value = eq[1]
#         for j in range(total_ops):
#             if i & (1 << j):
#                 value *= eq[j + 2]
#             else:
#                 value += eq[j + 2]
#         if value == eq[0]:
#             return True
#     return False


# print(sum(eq[0] for eq in equations if check_equation_true(eq)))