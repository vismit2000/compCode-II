# PROBLEM: https://cses.fi/problemset/task/3314/
# APPROACH: Cartesian Tree https://stackoverflow.com/questions/79751600/solve-cses-mountain-range-efficiently
n = int(input())
heights = list(map(int, input().split()))

# Build the Cartesian-like tree: up[i] = parent of mountain i.
# The tallest mountain is the root; equal heights in one segment share a single node.
up = {}
stack = [(float('inf'), None)]  # rightmost path of the tree, as (height, index)
for i, h in enumerate(heights):
    kid = None
    while h > stack[-1][0]:  # shorter mountains on the path become i's subtree
        kid = stack.pop()[1]
    if h < stack[-1][0]:  # i is a new node under the stack top
        up[i] = stack[-1][1]
        if kid is not None:
            up[kid] = i
        stack.append((h, i))
    # if h == stack top, i is the same node as the top, so nothing is added

# Tree depth: a parent is always taller than its child, so going from
# tallest to shortest, the parent's depth is always known already.
depth = {None: 0}
for i in sorted(up, key=lambda i: -heights[i]):
    depth[i] = depth[up[i]] + 1

print(max(depth.values()))
