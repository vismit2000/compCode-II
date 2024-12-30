with open("input.txt", "r") as file:
    block = file.read().strip().split("\n")[0]

disk = []
total_ids = (len(block) + 1) // 2
curr_id, curr_idx = 0, 0
file_counts = {}
file_idx = {}

for i, c in enumerate(block):
    val = int(c)
    if i % 2 == 0:
        disk += [curr_id] * val
        file_counts[curr_id] = val
        file_idx[curr_id] = curr_idx
        curr_id += 1
    else:
        disk += [-1] * val
    curr_idx += val
disk2 = disk.copy()

start, end = 0, len(disk) - 1
while start < end:
    while disk[start] != -1:
        start += 1
    while disk[end] == -1:
        end -= 1
    disk[start], disk[end] = disk[end], disk[start]
    start, end = start + 1, end - 1

print(sum(i * file for i, file in enumerate(disk) if file != -1))

disk = disk2
free_segments = {}
free_segment_len = 0
start = 0
for i, file in enumerate(disk):
    if file == -1:
        if free_segment_len == 0:
            start = i
        free_segment_len += 1
    elif free_segment_len > 0:
        free_segments[start] = free_segment_len
        free_segment_len = 0

for id in range(total_ids - 1, -1, -1):
    count = file_counts[id]
    idx = file_idx[id]
    for k, v in sorted(free_segments.items()):
        if k >= idx:
            break
        if v >= count:
            disk[k : k + count], disk[idx : idx + count] = [id] * count, [-1] * count
            if v > count:
                free_segments[k + count] = v - count
            del free_segments[k]
            break
    free_segments = dict(sorted(free_segments.items()))

print(sum(i * file for i, file in enumerate(disk) if file != -1))