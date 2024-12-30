import networkx as nx

with open("input.txt", "r") as file:
    lines = file.read().strip().split("\n")
    graph = {i + j * 1j: c for i, r in enumerate(lines) for j, c in enumerate(r)}

start = next(p for p in graph if graph[p] == "S")
end = next(p for p in graph if graph[p] == "E")

MOVE_COST, ROTATE_COST = 1, 1000
face = ("N", "E", "S", "W")


def dijkstra(start, end, graph):
    g = nx.DiGraph()
    for p, c in graph.items():
        if c != "#":
            for i, d in enumerate((-1, 1j, 1, -1j)):
                if graph.get(p + d, "#") != "#":
                    g.add_edge((p, face[i]), (p + d, face[i]), weight=MOVE_COST)
            for i, f in enumerate(face):
                g.add_edge((p, f), (p, face[(i + 1) % 4]), weight=ROTATE_COST)
                g.add_edge((p, f), (p, face[(i - 1) % 4]), weight=ROTATE_COST)

    for f in face:
        g.add_edge((end, f), end, weight=0)

    # Find all shortest paths - The weight='weight' parameter ensures that the paths are calculated based on the edge weights.
    all_paths = list(nx.all_shortest_paths(g, (start, "E"), end, weight="weight"))
    tiles = {p for path in all_paths for p, _ in path[:-1]}

    return nx.dijkstra_path_length(g, (start, "E"), end), len(tiles)


print(dijkstra(start, end, graph))