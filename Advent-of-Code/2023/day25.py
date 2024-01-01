import networkx as nx

content = open("input.txt", "r").read()
lines = content.split("\n")

G = nx.Graph()

for line in lines:
    left, right = line.split(": ")
    for node in right.split():
        G.add_edge(left, node)
        G.add_edge(node, left)

# 1) Visualization
# import matplotlib.pyplot as plt
# plt.rcParams["figure.figsize"] = (25, 25)
# nx.draw(G, with_labels=True, font_size=6, node_size=100)
# plt.savefig("foo.svg")

# 2) Fiedler vector - Algebraic connectivity: https://en.wikipedia.org/wiki/Algebraic_connectivity#Partitioning_a_graph_using_the_Fiedler_vector
# import math
# from collections import Counter

# counts = Counter(nx.fiedler_vector(G, normalized=True) > 0)
# print(math.prod(counts.values()))

# 3) Minimum edge cut (networkx) - Articulation points and bridges
G.remove_edges_from(nx.minimum_edge_cut(G))
first, second = nx.connected_components(G)
print(len(first) * len(second))

# 4) Fiedler vector - Algebraic connectivity (without networkx): https://www.reddit.com/r/adventofcode/comments/18qbsxs/comment/keubcfd/
import numpy as np
from collections import Counter, defaultdict

graph = defaultdict(set)
for line in lines:
    left, right = line.split(": ")
    for node in right.split():
        graph[left].add(node)
        graph[node].add(left)
n = len(graph)
index_to_node = list(graph.keys())
node_to_index = {node: index for index, node in enumerate(index_to_node)}
adjacency = np.zeros((n, n), dtype=int)
for node, neighbors in graph.items():
    for neighbor in neighbors:
        adjacency[node_to_index[node], node_to_index[neighbor]] = 1
        adjacency[node_to_index[neighbor], node_to_index[node]] = 1

laplacian = np.diag(np.sum(adjacency, axis=1)) - adjacency
eig = np.linalg.eig(laplacian)
eig_sort = np.argsort(eig.eigenvalues)
eigenvectors = eig.eigenvectors.T[eig_sort]
fiedler = eigenvectors[1]
counts = Counter(fiedler > 0)
print(np.prod(list(counts.values())))
