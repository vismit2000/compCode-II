# Conway's Game of Life

from itertools import chain

flatten = chain.from_iterable

content = open("input.txt", "r").read()
rules, image = content.split("\n\n")
rules = rules.replace("\n", "")
image = image.splitlines()


class Pixels(set):
    def __init__(self, pixels, color="#"):
        self.update(pixels)
        self.color = color


def neighborhood(point) -> list[tuple]:
    x, y = point
    return [(x + i, y + j) for i in (-1, 0, 1) for j in (-1, 0, 1)]


def pixel_sum(point, pixels) -> int:
    """
    The sum of 9 pixels in the neighborhood of a point.
    If pixels.color == light => Add up nbd points that are in pixels
    If pixels.color == dark => Add up nbd points that are not in pixels
    """
    return sum(
        (256 >> i) * ((p in pixels) == (pixels.color == "#"))
        for i, p in enumerate(neighborhood(point))
    )


def enhance(pixels, n=1, rules=rules) -> Pixels:
    for gen in range(n):
        # opposite_color = "#" # for sample
        opposite_color = "." if pixels.color == "#" else "#"
        candidates = set(flatten(map(neighborhood, pixels)))
        pixels = Pixels(
            (
                point
                for point in candidates
                if rules[pixel_sum(point, pixels)] == opposite_color
            ),
            opposite_color,
        )

    return pixels


pixels = Pixels(
    (i, j)
    for i in range(len(image))
    for j in range(len(image[0]))
    if image[i][j] == "#"
)

print(len(enhance(pixels, 2)))
print(len(enhance(pixels, 50)))
