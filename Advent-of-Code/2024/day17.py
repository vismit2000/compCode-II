import re

with open("input.txt", "r") as file:
    lines = file.read().strip().split("\n\n")
    A, B, C = tuple(map(int, re.findall(r"\d+", lines[0])))
    program = tuple(map(int, re.findall(r"\d+", lines[1])))


def combo(v):
    return A if v == 4 else B if v == 5 else C if v == 6 else v


def execute(opcode, operand, pc):
    global A, B, C
    pc_updated, out = pc + 2, None
    match opcode:
        case 0:
            A = A // (2 ** combo(operand))
        case 1:
            B ^= operand
        case 2:
            B = combo(operand) % 8
        case 3:
            if A:
                pc_updated = operand
        case 4:
            B ^= C
        case 5:
            out = combo(operand) % 8
        case 6:
            B = A // (2 ** combo(operand))
        case 7:
            C = A // (2 ** combo(operand))
    return pc_updated, out


def run(program):
    pc = 0
    output = []
    while pc < len(program) - 1:
        opcode, operand = program[pc], program[pc + 1]
        pc_updated, out = execute(opcode, operand, pc)
        pc = pc_updated
        if out is not None:
            output += [str(out)]
    return output


print(",".join(run(program)))


"""Input: (vismit2000)

Register A: 30344604
Register B: 0
Register C: 0

Program: 2,4,1,1,7,5,1,5,4,5,0,3,5,5,3,0
"""