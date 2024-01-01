# content = open("input.txt", "r").read()
# lines = content.split("\n")
# n, m = len(lines), len(lines[0])

# patterns, groups = [], []
# for line in lines:
#     pattern, group = line.split()
#     pattern = pattern.replace(".", "0")
#     pattern = pattern.replace("#", "1")
#     patterns.append(pattern)
#     groups.append([int(g) for g in group.split(",")])

# ans = 0
# for i in range(n):
#     # Try to replace each ? with . and # and check if condition for contiguous groups is satisfied
#     combs = 0
#     n_qmarks = patterns[i].count("?")
#     for j in range(2**n_qmarks):
#         bin_str = bin(j)[2:].zfill(n_qmarks)
#         idx = 0
#         new_pattern = ""
#         for k in range(len(patterns[i])):
#             if patterns[i][k] == "?":
#                 new_pattern += bin_str[idx]
#                 idx += 1
#             else:
#                 new_pattern += patterns[i][k]
#         # print(new_pattern)
#         consecutive_ones = [
#             len(group) for group in new_pattern.split("0") if group.startswith("1")
#         ]
#         # print(consecutive_ones)
#         # print(consecutive_ones == groups[i])
#         if consecutive_ones == groups[i]:
#             combs += 1
#     print(i, combs)
#     ans += combs
# print(ans)

content = open("input.txt", "r").read()
lines = content.split("\n")
n, m = len(lines), len(lines[0])

factor = 5

from functools import cache


@cache
def count(pattern, group):
    if group == ():
        return 0 if "#" in pattern else 1
    res = 0
    n = group[0]
    for i in range(len(pattern) - len(group) - sum(group) + 1):
        if pattern[i + n] == "#":
            continue
        if "#" in pattern[:i]:
            break
        if "." not in pattern[i : i + n]:
            res += count(pattern[i + n + 1 :], group[1:])
    return res


ans = 0
for line in lines:
    pattern, group = line.split()
    pattern = "?".join([pattern] * factor)
    pattern += "."
    group = factor * tuple(map(int, group.split(",")))
    cnt = count(pattern, group)
    ans += cnt
print(ans)
