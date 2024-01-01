content = open("input.txt", "r").read()
lines = content.split("\n")


def hash(seq, cv):
    for ch in seq:
        cv = (17 * (cv + ord(ch))) % 256
    return cv


part1, part2 = 0, 0
init_seq = lines[0].split(",")
boxes = [{} for _ in range(256)]
for seq in init_seq:
    part1 += hash(seq, 0)
    label = seq[:-1] if seq[-1] == "-" else seq[:-2]
    box_id = hash(label, 0)
    if seq[-1] == "-":
        boxes[box_id].pop(label, None)
    else:
        boxes[box_id][label] = int(seq[-1])

for i, box in enumerate(boxes, 1):
    for slot, (label, focal_length) in enumerate(box.items(), 1):
        part2 += i * slot * focal_length
print(part1, part2)
