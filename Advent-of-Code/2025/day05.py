# Merge overlapping intervals

import re

with open("input.txt", "r") as file:
    intervals, ingredients = file.read().strip().split("\n\n")
    intervals = [tuple(map(int, re.findall(r"\d+", r))) for r in intervals.split("\n")]
    ingredients = list(map(int, ingredients.split("\n")))

count_in_range = 0
for ingredient in ingredients:
    if any(start <= ingredient <= end for start, end in intervals):
        count_in_range += 1
print(count_in_range)


def merge_intervals(intervals):
    sorted_intervals = sorted(intervals, key=lambda x: x[0])
    merged = [sorted_intervals[0]]

    for current_start, current_end in sorted_intervals[1:]:
        last_start, last_end = merged[-1]

        # If current interval overlaps or is adjacent to the last merged interval
        if current_start <= last_end + 1:
            # Merge by extending the end of the last interval
            merged[-1] = (last_start, max(last_end, current_end))
        else:  # No overlap, add as a new interval
            merged.append((current_start, current_end))

    return merged


print(sum([end - start + 1 for start, end in merge_intervals(intervals)]))