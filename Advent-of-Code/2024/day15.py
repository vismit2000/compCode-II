with open("input.txt", "r") as file:
    lines = file.read().strip().split("\n\n")
    grid = lines[0].split("\n")
    graph1 = {i + j * 1j: c for i, r in enumerate(grid) for j, c in enumerate(r)}
    grid = [
        r.replace("#", "##").replace(".", "..").replace("O", "[]").replace("@", "@.")
        for r in grid
    ]
    graph2 = {i + j * 1j: c for i, r in enumerate(grid) for j, c in enumerate(r)}
    moves = "".join(lines[1:]).replace("\n", "")
    dirs = {"^": -1, "v": 1, "<": -1j, ">": 1j}


def can_move(graph, box_pos, dir):
    if graph[box_pos] in ".#":
        return graph[box_pos] == "."
    other_box_pos = box_pos - 1j if graph[box_pos] == "]" else box_pos + 1j
    return can_move(graph, box_pos + dir, dir) and can_move(
        graph, other_box_pos + dir, dir
    )


def move_one_step(graph, pos, dir):
    next_step = pos + dir
    if graph[next_step] == ".":
        graph[pos], graph[next_step] = graph[next_step], graph[pos]
        return
    box_pos = next_step
    other_box_pos = box_pos - 1j if graph[box_pos] == "]" else box_pos + 1j
    move_one_step(graph, box_pos, dir)
    move_one_step(graph, other_box_pos, dir)
    graph[pos], graph[next_step] = graph[next_step], graph[pos]


def attempt(graph, robot, dir, box):
    pos = robot + dir
    while graph[pos] not in "#.":
        pos += dir

    if graph[pos] == "#":
        return robot

    if dir in (-1j, 1j) or box == "O":
        while pos != robot:
            graph[pos], graph[pos - dir] = graph[pos - dir], graph[pos]
            pos -= dir
        return robot + dir

    if can_move(graph, robot + dir, dir):
        move_one_step(graph, robot, dir)
        return robot + dir
    return robot


def simulate(graph, box):
    robot = next(p for p in graph if graph[p] == "@")
    for move in moves:
        robot = attempt(graph, robot, dirs[move], box)
    return int(sum(100 * p.real + p.imag for p in graph if graph[p] == box))


print(simulate(graph1, "O"))
print(simulate(graph2, "["))