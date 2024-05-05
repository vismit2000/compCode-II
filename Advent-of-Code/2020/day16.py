# Similar to exact cover (Sudoku variant)

import re
from collections import namedtuple
from math import prod

content = open("input.txt", "r").read()

TicketData = namedtuple("TicketData", "fields, your, nearby")


def ints(text: str) -> tuple[int]:
    "Return a tuple of all the integers in text."
    return tuple(map(int, re.findall("-?[0-9]+", text)))


class Sets(tuple):
    "A tuple of set-like objects (such as ranges); supports `in`."

    def __contains__(self, item):
        return any(item in s for s in self)


def parse_ticket_line(line: str) -> tuple[str, Sets]:
    "Parse 'row: 10-20 or 30-40' to ('row', Sets((range(10, 21), range(30, 41))))."
    field = line.split(":")[0]
    a, b, c, d = ints(line.replace("-", " "))
    return field, Sets((range(a, b + 1), range(c, d + 1)))


def parse_ticket_data(fieldstr: str, your: str, nearby: str) -> TicketData:
    fields = dict(map(parse_ticket_line, fieldstr.splitlines()))
    your = ints(your.splitlines()[1])
    nearby = [ints(line) for line in nearby.splitlines()[1:]]
    return TicketData(fields, your, nearby)


ticket_data = parse_ticket_data(*content.split("\n\n"))

# Part 1
ranges = Sets(ticket_data.fields.values())
print(sum(v for ticket in ticket_data.nearby for v in ticket if v not in ranges))


# Part 2
## First find the valid tickets.
## Then start with the assumption that any field name is possible for any index number in the tickets.
## Determine what field names are invalid for what ticket index numbers.
## Remove the field name from the possibilities for that index, and if there is only one possible field name left, then remove it from all other index positions.
def valid_ticket(ticket, ranges) -> bool:
    return all(v in ranges for v in ticket)


def invalid_fields(valid, fields) -> tuple[str, int]:
    "Yield (field_name, field_number) for all invalid fields."
    return (
        (field_name, i)
        for ticket in valid
        for i in range(len(ticket))
        for field_name in fields
        if ticket[i] not in fields[field_name]
    )


def eliminate_others(possible, i):
    "Eliminate possible[i] from all other possible[j]."
    for j in possible:
        if j != i:
            possible[j] -= possible[i]


def decode_tickets(ticket_data) -> dict[str, int]:
    "Return a mapping of {field_name: field_number} (index into ticket)."
    fields, your, nearby = ticket_data
    ranges = Sets(ticket_data.fields.values())
    valid = [t for t in nearby + [your] if valid_ticket(t, ranges)]
    possible = {i: set(fields) for i in range(len(your))}
    while any(len(possible[i]) > 1 for i in possible):
        for field_name, i in invalid_fields(valid, fields):
            possible[i] -= {field_name}
            if len(possible[i]) == 1:
                eliminate_others(possible, i)
    return {field: i for i, [field] in possible.items()}


code = decode_tickets(ticket_data)
print(
    prod(
        ticket_data.your[code[field]] for field in code if field.startswith("departure")
    )
)
