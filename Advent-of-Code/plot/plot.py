import matplotlib.pyplot as plt
import networkx as nx

# Graph data
raw = """
svr: aaa bbb
aaa: fft
fft: ccc
bbb: tty
tty: ccc
ccc: ddd eee
ddd: hub
hub: fff
eee: dac
dac: fff
fff: ggg hhh
ggg: out
hhh: out
"""

with open("input.txt") as f:
    raw = f.read()

# Build graph
G = nx.DiGraph()
for line in raw.strip().split("\n"):
    src, rest = line.split(":")
    src = src.strip()
    targets = rest.strip().split()
    for t in targets:
        G.add_edge(src, t)

print(len(list(nx.all_simple_paths(G, "svr", "fft"))))
# # Special node colors
# special_colors = {
#     "svr": "tab:green",
#     "fft": "tab:orange",
#     "dac": "tab:purple",
#     "out": "tab:red",
# }

# # Assign colors
# node_colors = [special_colors.get(n, "lightgray") for n in G.nodes()]

# # Layout
# pos = nx.spring_layout(G, seed=42)

# # Draw graph
# plt.figure(figsize=(10, 8))
# nx.draw_networkx_nodes(G, pos, node_color=node_colors, node_size=300)
# nx.draw_networkx_labels(G, pos, font_size=5)
# nx.draw_networkx_edges(G, pos, arrows=True, arrowstyle="-|>", arrowsize=5)

# plt.axis("off")
# plt.tight_layout()
# plt.show()
