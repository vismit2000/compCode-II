import re
import operator

with open("input.txt", "r") as file:
    lines = file.read().strip().split("\n")
    connections = [tuple(re.findall("[a-zA-Z0-9]+", line)) for line in lines]
    operators = dict(XOR=operator.xor, AND=min, OR=max)


class Device(dict):
    """A mapping of {wire_name: bit_value_or_gate}, assembled from a device specification."""

    def __init__(self, lines):
        for line in lines:
            match line:
                case (wire, bit):  # e.g., ('x00', 1)
                    self[wire] = int(bit)
                case (x, op, y, wire):  # e.g., ('y33', 'AND', 'x33', 'bfn')
                    self[wire] = (x, op, y)


def wires(device: Device, letter: str) -> list[str]:
    """The names of all the wires that start with the given letter, in sorted order."""
    return sorted([w for w in device if w.startswith(letter)], reverse=True)


def simulate(device: Device) -> str:
    """Use dataflow to get the values of the output bits of this device (as a "01" str)."""

    def get(w) -> int:
        match device[w]:
            case (x, op, y):
                return operators[op](get(x), get(y))
            case bit:
                return bit

    return "".join(str(bit) for bit in map(get, wires(device, "z")))


print(int(simulate(Device(connections)), base=2))
