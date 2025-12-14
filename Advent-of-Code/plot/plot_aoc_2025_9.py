import matplotlib.pyplot as plt

with open("input.txt") as f:
    lines = f.read().strip().split("\n")
    points = [tuple(map(int, line.split(","))) for line in lines]

x = [p[0] for p in points]
y = [p[1] for p in points]

plt.figure(figsize=(6,6))
plt.scatter(x, y, s=30)

# Label each point
# for px, py in points:
#     plt.text(px, py, f"{px},{py}", fontsize=8)

# Add grid but NOT forced to match every coordinate
plt.grid(True, linestyle="--", alpha=0.6)

# Expand view just slightly around points
padding = max((max(x)-min(x)), (max(y)-min(y))) * 0.1 + 1
plt.xlim(min(x) - padding, max(x) + padding)
plt.ylim(min(y) - padding, max(y) + padding)

plt.title("Point Visualization")
plt.show()
