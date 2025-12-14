import re
from collections import deque
from dataclasses import dataclass


@dataclass
class Machine:
    diagram: int
    buttons: tuple[int]
    jolts: list[int]


with open("input.txt") as f:
    lines = f.read().strip().split("\n")
    machines = [
        (
            d := re.findall(r"\[(.*?)\]|\((.*?)\)|\{(.*?)\}", line),
            Machine(
                diagram=sum((1 if c == "#" else 0) << i for i, c in enumerate(d[0][0])),
                buttons=tuple(
                    sum(1 << int(n) for n in x.split(",")) for _, x, _ in d[1:-1]
                ),
                jolts=list(map(int, d[-1][2].split(","))),
            ),
        )[1]
        for line in lines
    ]


def min_button_presses(start: int, buttons: tuple[int]) -> int | None:
    if start == 0:
        return 0

    q = deque([(start, 0)])  # (current_state, presses_so_far)
    seen = {start}

    while q:
        state, dist = q.popleft()
        for b in buttons:
            nxt = state ^ b
            if nxt == 0:
                return dist + 1
            if nxt not in seen:
                seen.add(nxt)
                q.append((nxt, dist + 1))

    return None


print(sum(min_button_presses(machine.diagram, machine.buttons) for machine in machines))

# Part 2 - USing z3
from z3 import Int, Optimize, Sum, sat
import numpy as np

total = 0
for machine in machines:
    # A has shape (num_buttons, num_jolts)
    A = np.array(
        [
            [(button >> i) & 1 for i in range(len(machine.jolts))]
            for button in machine.buttons
        ],
        dtype=int,   # keep as ints (0/1)
    )
    b = np.array(machine.jolts, dtype=int)

    # We want A.T @ x = B
    A= A.T                      # (num_jolts, num_buttons)

    num_eqs, num_vars = A.shape  # rows, cols

    opt = Optimize()

    # Integer vars x_0, x_1, ..., x_{num_vars-1}
    xs = [Int(f"x_{i}") for i in range(num_vars)]

    for x in xs: # x_i >= 0
        opt.add(x >= 0)

    # Constraints: for each j, sum_i A[j, i] * x_i == b[j]
    for j in range(num_eqs):
        opt.add(Sum(A[j, i] * xs[i] for i in range(num_vars)) == int(b[j]))

    opt.minimize(Sum(xs)) # Objective: minimize sum(x_i)

    # Solve
    if opt.check() == sat:
        model = opt.model()
        x_vals = np.array([model[x].as_long() for x in xs], dtype=int)
        print(x_vals, "sum =", x_vals.sum())
        total += x_vals.sum()
    else:
        print("No integer solution for this machine")
print(total)

# Part 2 - using scipy.optimize linprog
from itertools import combinations
from scipy.optimize import linprog

a = b = 0
for lights, *buttons, jolts in map(str.split, open('input.txt')):
    lights = [c=='#' for c in lights[1:-1]]
    buttons = [eval(b[:-1]+',)') for b in buttons]
    jolts = eval(jolts[1:-1])

    def toggle(buttons):
        for n in range(len(buttons)):
            for pressed in combinations(buttons, n):
                state = [sum(i in p for p in pressed) % 2
                    for i in range(len(lights))]
                if state == lights: return n

    a += toggle(buttons)

    costs = [1 for b in buttons]
    eqs = [[i in b for b in buttons] for i in range(len(jolts))]

    b += linprog(costs, A_eq=eqs, b_eq=jolts, integrality=1).fun

print(a, int(b))