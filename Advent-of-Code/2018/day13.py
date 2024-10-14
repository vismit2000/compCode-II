from dataclasses import dataclass
from itertools import cycle

Point = complex

alphabet = "abcdefghijklmnopqrstuvwxyz"

content = open("input.txt", "r").read()
lines = content.split("\n")


def first(iterable, default=None):
    "Return first item in iterable, or default."
    return next(iter(iterable), default)


def X(point):
    return point.real if isinstance(point, complex) else point[0]


def Y(point):
    return point.imag if isinstance(point, complex) else point[1]


# Headings: HU, HD, HR, HL = Head up, down, right, left
# Turns:    TL, TR, TS, TB = Turn left, right, straight, backwards
HU = TL = Point(0, -1)
HD = TR = -TL
HR = TS = Point(1, 0)
HL = TB = -TS

headings = {">": HR, "<": HL, "^": HU, "v": HD}
inverse_headings = dict((headings[ch], ch) for ch in headings)

assert (
    HU * TR == HR and TR**4 == TL**4 == TS and HR * TB == HL and HU == -HD and TR == -TL
)


@dataclass
class Cart:
    name: str
    pos: Point
    heading: Point
    turns: object


@dataclass
class World:
    grid: tuple
    carts: list

    def __init__(self, lines):
        table = str.maketrans("<>^v", "--||")
        names = cycle(alphabet)
        self.grid = [line.translate(table) for line in lines]
        self.carts = [
            Cart(next(names), Point(x, y), headings[h], cycle((TL, TS, TR)))
            for (y, line) in enumerate(lines)
            for (x, h) in enumerate(line)
            if h in headings
        ]

    def __getitem__(self, point):
        return self.grid[int(Y(point))][int(X(point))]

    def show(self):
        "Print a representation of the world."
        for y, line in enumerate(self.grid):
            for x, ch in enumerate(line):
                cart = first(c for c in self.carts if c.pos == Point(x, y))
                ch = inverse_headings[cart.heading] if cart else ch
                print(ch, end="")
            print()
        print()


def madmad(world, show=False):
    "Simulate the mine cart madness until a collision."
    while True:
        if show:
            world.show()
        for cart in sorted(world.carts, key=lambda c: (Y(c.pos), X(c.pos))):
            cart.heading *= turn(cart, world)
            cart.pos += cart.heading
            if collision(cart, world):
                if show:
                    world.show()
                return cart.pos


def madmad2(world, show=False):
    "Simulate the mine cart madness until a collision."
    while True:
        if len(world.carts) == 1:
            return world.carts[0].pos
        if show:
            world.show()
        for cart in sorted(world.carts, key=lambda c: (Y(c.pos), X(c.pos))):
            cart.heading *= turn(cart, world)
            cart.pos += cart.heading
            other = collision(cart, world)
            if other:
                if show:
                    world.show()
                # Remove the two carts
                world.carts = [c for c in world.carts if c.pos not in (cart.pos, other)]


def turn(cart, world):
    "Which way should the cart turn (depends on character it is on)."
    ch = world[cart.pos]
    if ch == "+":
        return next(cart.turns)
    if ch == "/":
        return TR if cart.heading in (HU, HD) else TL
    if ch == "\\":
        return TR if cart.heading in (HR, HL) else TL
    else:
        return TS


def collision(cart, world):
    "Has this cart collided with any other cart?"
    return first(
        other.pos
        for other in world.carts
        if other is not cart and cart.pos == other.pos
    )


example = r"""
/->-\         
|   |  /----\ 
| /-+--+-\  | 
| | |  | v  | 
\-+-/  \-+--/ 
  \------/     
""".strip().splitlines()

# print(madmad(World(example), False))
print(madmad2(World(lines), False))
