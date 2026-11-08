import math

with open("../input.txt") as f:
    data = f.read()
    cones = list(map(int, data.split(",")))

# ans = 0
# for cone in cones:
#     sqrt = math.floor(cone ** 0.5)
#     if sqrt * sqrt != cone:
#         ans += (sqrt + 1) ** 2 - cone
# print(ans)

ans = 0
for cone in cones:
    if cone < 8:
        ans += 8 - cone
        continue
    sqrt = math.isqrt(cone // 4)
    if 4 * sqrt * (sqrt + 1) < cone:
        ans += 4 * (sqrt + 1) * (sqrt + 2) - cone
    elif 4 * sqrt * (sqrt + 1) > cone:
        ans += 4 * sqrt * (sqrt + 1) - cone
print(ans)