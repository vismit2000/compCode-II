# content = open("input.txt", "r").read()
# lines = content.split("\n")
# lines = ["button -> broadcaster"] + lines


# def build_graph(lines):
#     graph = {}
#     for line in lines:
#         node, children = line.split(" -> ")
#         node_type = node[0]
#         if node[0] in "%&":
#             node = node[1:]
#         children = children.split(", ")
#         if node not in graph:
#             graph[node] = {}

#         graph[node]["state"] = 0
#         graph[node]["type"] = node_type
#         graph[node]["children"] = children

#         for child in children:
#             if child not in graph:
#                 graph[child] = {}
#             if "parents" not in graph[child]:
#                 graph[child]["parents"] = {}
#             graph[child]["parents"][node] = 0
#     return graph


# def push_button(graph: dict) -> dict:
#     queue = [(0, "button", "broadcaster")]
#     pulse_count = {0: 0, 1: 0}

#     while queue:
#         pulse, sender, receiver = queue.pop(0)
#         pulse_count[pulse] += 1

#         if "type" not in graph[receiver]:
#             continue

#         if graph[receiver]["type"] == "%":
#             if pulse == 1:
#                 continue
#             graph[receiver]["state"] = 1 - graph[receiver]["state"]
#             for child in graph[receiver]["children"]:
#                 queue.append((graph[receiver]["state"], receiver, child))

#         elif graph[receiver]["type"] == "&":
#             graph[receiver]["parents"][sender] = pulse
#             send_pulse = 1 if 0 in graph[receiver]["parents"].values() else 0
#             for child in graph[receiver]["children"]:
#                 queue.append((send_pulse, receiver, child))

#         else:
#             graph[receiver]["state"] = pulse
#             for child in graph[receiver]["children"]:
#                 queue.append((pulse, receiver, child))

#     return pulse_count


# graph = build_graph(lines)

# # import pprint

# # pprint.pprint(graph)

# total_pulse_count = {0: 0, 1: 0}
# for i in range(1000):
#     pulse_count = push_button(graph)
#     total_pulse_count[0] += pulse_count[0]
#     total_pulse_count[1] += pulse_count[1]

# print(total_pulse_count)
# print(total_pulse_count[0] * total_pulse_count[1])


import math

content = open("input.txt", "r").read()
lines = content.split("\n")
lines = ["button -> broadcaster"] + lines


def build_graph(lines):
    graph = {}
    for line in lines:
        node, children = line.split(" -> ")
        node_type = node[0]
        if node[0] in "%&":
            node = node[1:]
        children = children.split(", ")
        if node not in graph:
            graph[node] = {}

        graph[node]["state"] = 0
        graph[node]["type"] = node_type
        graph[node]["children"] = children

        for child in children:
            if child not in graph:
                graph[child] = {}
            if "parents" not in graph[child]:
                graph[child]["parents"] = {}
            graph[child]["parents"][node] = 0
    return graph


def push_button(graph: dict, target: str) -> bool:
    queue = [(0, "button", "broadcaster")]
    pulse_count = {0: 0, 1: 0}

    while queue:
        pulse, sender, receiver = queue.pop(0)
        if receiver == target and pulse == 0:
            return True
        pulse_count[pulse] += 1

        if "type" not in graph[receiver]:
            continue

        if graph[receiver]["type"] == "%":
            if pulse == 1:
                continue
            graph[receiver]["state"] = 1 - graph[receiver]["state"]
            for child in graph[receiver]["children"]:
                queue.append((graph[receiver]["state"], receiver, child))

        elif graph[receiver]["type"] == "&":
            graph[receiver]["parents"][sender] = pulse
            send_pulse = 1 if 0 in graph[receiver]["parents"].values() else 0
            for child in graph[receiver]["children"]:
                queue.append((send_pulse, receiver, child))

        else:
            graph[receiver]["state"] = pulse
            for child in graph[receiver]["children"]:
                queue.append((pulse, receiver, child))

    return False


lcm_list = []
graph = build_graph(lines)
targets = graph["cn"]["parents"].keys()

for parent in targets:
    graph = build_graph(lines)
    i = 1
    while not push_button(graph, parent):
        i += 1
    lcm_list.append(i)

print(lcm_list)
print(math.lcm(*lcm_list))
