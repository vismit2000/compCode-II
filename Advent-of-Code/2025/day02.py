import itertools

with open("input.txt") as f:
    prod_ranges = [tuple(map(int, pair.split("-"))) for pair in f.read().split(",")]

def check_invalid(num_str):
    for i in range(1, len(num_str) // 2 + 1):
        if len(set(itertools.batched(num_str, i))) == 1:
            return True
    return False

print(sum([num for (start, end) in prod_ranges for num in range(start, end + 1) if check_invalid(str(num))]))