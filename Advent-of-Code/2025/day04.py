with open("input.txt") as f:
    lines = f.read().strip().split("\n")
    graph = {i + j * 1j: c for i, r in enumerate(lines) for j, c in enumerate(r)}

def neighbours(pos):
    return (pos + 1, pos - 1, pos + 1j, pos - 1j, pos + 1 + 1j, pos + 1 - 1j, pos - 1 + 1j, pos - 1 - 1j)

rolls = 0
while True:
    removed = []
    for pos in graph:
        if graph[pos] == '@':
            cnt = sum(1 for n in neighbours(pos) if n in graph and graph[n] == '@')
            if cnt < 4:
                removed.append(pos)
                rolls += 1
    for pos in removed:
        graph[pos] = "."
    if not removed:
        break
print(rolls)