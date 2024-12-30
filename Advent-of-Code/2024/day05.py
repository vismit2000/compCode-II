from functools import cmp_to_key

with open("input.txt", "r") as file:
    lines = file.read().strip().split("\n")
    page_orders = [tuple(map(int, line.split("|"))) for line in lines if "|" in line]
    updates = [tuple(map(int, line.split(","))) for line in lines if "," in line]


def is_order_followed(update):
    return not any((v1, v2) not in page_orders for v1, v2 in zip(update, update[1:]))


def rule_lookup(m, n):
    return +1 if (m, n) in page_orders else -1


ans1, ans2 = 0, 0
for idx, update in enumerate(updates):
    if is_order_followed(update):
        ans1 += update[len(update) // 2]
    else:
        new_update = sorted(update, key=cmp_to_key(rule_lookup))
        ans2 += new_update[len(new_update) // 2]

print(ans1, ans2)