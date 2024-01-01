content = open("input.txt", "r").read()
lines = content.split("\n")


def flow_through_map(map, mapping):
    new_mapping = []
    for range_start, range_end in mapping:
        done = False
        for start, end, diff in map:
            if range_start > end:
                continue
            elif range_end < start:
                new_mapping.append((range_start, range_end))
                done = True
                break
            elif range_start >= start and range_end <= end:
                new_mapping.append((range_start + diff, range_end + diff))
                done = True
                break
            elif range_start < start and range_end <= end:
                new_mapping.append((range_start, start - 1))
                new_mapping.append((start + diff, range_end + diff))
                done = True
                break
            elif range_start >= start and range_end > end:
                new_mapping.append((range_start + diff, end + diff))
                range_start = end + 1
        if not done:
            new_mapping.append((range_start, range_end))

    # for i in range(len(mapping)):
    #     for start, end, diff in map:
    #         if mapping[i] >= start and mapping[i] <= end:
    #             new_mapping[i] += diff
    #             break
    new_mapping.sort()
    return new_mapping


all_maps = {}
map_name = ""
for line in lines[2:]:
    if line == "":
        continue
    if line[0] >= "a" and line[0] <= "z":
        map_name = line
        all_maps[map_name] = []
    else:
        dest_start, source_start, range_length = [int(num) for num in line.split()]
        all_maps[map_name].append(
            source_start,
            source_start + range_length - 1,
            dest_start - source_start,
        )
for key in all_maps:
    all_maps[key].sort()

elements = [
    "seed",
    "soil",
    "fertilizer",
    "water",
    "light",
    "temperature",
    "humidity",
    "location",
]

seeds = [int(seed) for seed in lines[0].split(": ")[1].split(" ")]
part_1_seeds = [(seed, seed) for seed in seeds]
part_2_seeds = [
    (seeds[i], seeds[i] + seeds[i + 1] - 1) for i in range(0, len(seeds), 2)
]
part_2_seeds.sort()

mapping = part_2_seeds  # or part_1_seeds
for i in range(len(elements) - 1):
    next_mapping = flow_through_map(
        all_maps[f"{elements[i]}-to-{elements[i+1]} map:"], mapping
    )
    mapping = next_mapping

print(mapping[0][0])
