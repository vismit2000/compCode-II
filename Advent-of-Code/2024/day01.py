with open("input.txt", "r") as file:
    lines = file.read().strip().split("\n")

pairs = [list(map(int, line.split())) for line in lines]
first_elements = [pair[0] for pair in pairs]
second_elements = [pair[1] for pair in pairs]

second_freq = {
    element: second_elements.count(element) for element in set(second_elements)
}

total_difference = sum(
    abs(f - s) for f, s in zip(sorted(first_elements), sorted(second_elements))
)

weighted_difference = sum(abs(f * second_freq.get(f, 0)) for f in first_elements)
print(total_difference, weighted_difference)