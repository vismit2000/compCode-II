import networkx as nx

with open("input.txt", "r") as file:
    lines = file.read().strip().split("\n")
    g = nx.Graph()
    nodes = set()
    for line in lines:
        a, b = line.split("-")
        g.add_edge(a, b)

t_nodes = [node for node in g.nodes if node.startswith("t")]
party = set()
for t_node in t_nodes:
    for nbr1 in g.neighbors(t_node):
        for nbr2 in g.neighbors(nbr1):
            if nbr1 != t_node and g.has_edge(nbr2, t_node):
                party.add(tuple(sorted([t_node, nbr1, nbr2])))
print(len(party))

all_cliques = list(nx.find_cliques(g))
max_clique = max(all_cliques, key=len)
print(",".join(sorted(max_clique)))


def expand_clique(node, graph, clique=None):
    if clique is None:
        clique = set()
    clique.add(node)
    for nbr in graph.neighbors(node):
        if nbr not in clique and clique.issubset(set(graph.neighbors(nbr))):
            expand_clique(nbr, graph, clique)
    return clique


def max_clique(graph):
    return max((expand_clique(node, graph) for node in graph), key=len)


print(",".join(sorted(max_clique(g))))