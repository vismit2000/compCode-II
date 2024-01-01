content = open("input.txt", "r").read()
lines = content.split("\n")

# generate output as a dot file for plotting with graphviz


for line in lines:
    node, children = line.split(" -> ")
    if node[0] == "&":
        print(f"{node[1:]} [shape=diamond]")
        print(line[1:])
    elif node[0] == "%":
        print(f"{node[1:]} [shape=circle]")
        print(line[1:])
    else:
        print(f"{node} [shape=box]")
        print(line)
