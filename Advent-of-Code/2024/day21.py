from functools import cache

with open("input.txt", "r") as file:
    codes = file.read().strip().split("\n")


class Keypad(dict):
    """A representation of the key positions in a keypad."""

    def __init__(self, rows):
        self.update(
            {
                char: x + 1j * y
                for (y, row) in enumerate(rows)
                for (x, char) in enumerate(row)
            }
        )
        self.forbidden = self["_"]
        del self["_"]


numeric_keypad = Keypad(["789", "456", "123", "_0A"])
remote_keypad = Keypad(["_^A", "<v>"])


def possible_paths(key1, key2, keypad):
    pos1, pos2 = keypad[key1], keypad[key2]
    diff = pos2 - pos1
    dx, dy = int(diff.real), int(diff.imag)
    horizontal = abs(dx) * (">" if dx > 0 else "<")
    vertical = abs(dy) * ("v" if dy > 0 else "^")
    if pos1 + dx != keypad.forbidden:
        yield horizontal + vertical + "A"
    if pos1 + 1j * dy != keypad.forbidden:
        yield vertical + horizontal + "A"


def sliding_window(iterable, size):
    return [iterable[i : i + size] for i in range(len(iterable) - size + 1)]


def min_keypresses(code: str, levels: int) -> int:
    """The smallest possible number of keypresses (on the top level) to type `code` on the numeric keypad, if there are `levels` of button-pressers (all but one of them using the remote keypad)."""

    def total_presses(keysequence: str, level: int) -> int:
        """Total presses required to command `keysequence` from this level."""
        if level == 1:
            return len(keysequence)  # Just press the code buttons
        else:
            return sum(
                one_button_min_keypresses(key1, key2, level)
                for key1, key2 in sliding_window("A" + keysequence, 2)
            )

    @cache
    def one_button_min_keypresses(key1, key2, level):
        """The minimum number of presses to command a press of key2, starting from key1."""
        keypad = numeric_keypad if level == levels else remote_keypad
        return min(
            total_presses(path, level - 1)
            for path in possible_paths(key1, key2, keypad)
        )

    return total_presses(code, levels)


def complexity(code, levels=4):
    return int(code[:-1]) * min_keypresses(code, levels)


print(sum(map(complexity, codes)))
print(sum(complexity(code, levels=27) for code in codes))