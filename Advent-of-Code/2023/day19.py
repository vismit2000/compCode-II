content = open("input.txt", "r").read()
workflows, ratings = content.split("\n\n")

workflows = {
    workflow.split("{")[0]: tuple(workflow.split("{")[1][:-1].split(","))
    for workflow in workflows.split("\n")
}
ratings = [
    tuple([int(category[2:]) for category in rating[1:-1].split(",")])
    for rating in ratings.split("\n")
]


def apply_workflow(workflow, rating):
    x, m, a, s = rating
    for rule in workflow:
        if ":" not in rule:
            return rule
        cond, result = rule.split(":")
        if eval(cond):
            return result


ans = 0
for rating in ratings:
    status = apply_workflow(workflows["in"], rating)
    while status not in ("A", "R"):
        status = apply_workflow(workflows[status], rating)
    if status == "A":
        ans += sum(rating)

print(ans)


content = open("input.txt", "r").read()
workflows, ratings = content.split("\n\n")

workflows = {
    workflow.split("{")[0]: tuple(workflow.split("{")[1][:-1].split(","))
    for workflow in workflows.split("\n")
}
ratings = [
    tuple([int(category[2:]) for category in rating[1:-1].split(",")])
    for rating in ratings.split("\n")
]

accepted_conds = []


def build_graph(workflows):
    queue = [("in", "True")]
    while queue:
        node, prev_cond = queue.pop(0)
        if node == "A":
            accepted_conds.append(prev_cond)
            continue
        if node == "R":
            continue

        new_cond = "True"
        for rule in workflows[node]:
            if ":" not in rule:
                queue.append((rule, f"{prev_cond} and {new_cond}"))
                continue
            cond, result = rule.split(":")
            queue.append((result, f"{prev_cond} and {new_cond} and {cond}"))
            cond = cond.replace("<", ">=") if "<" in cond else cond.replace(">", "<=")
            new_cond = f"{new_cond} and {cond}"


build_graph(workflows)

ans = 0
for accepted in accepted_conds:
    accepted = accepted.split(" and ")
    dmin = {"x": 1, "m": 1, "a": 1, "s": 1}
    dmax = {"x": 4000, "m": 4000, "a": 4000, "s": 4000}
    for cond in accepted:
        if cond != "True":
            if cond[1] == "<":
                if cond[2] == "=":
                    dmax[cond[0]] = min(dmax[cond[0]], int(cond[3:]))
                else:
                    dmax[cond[0]] = min(dmax[cond[0]], int(cond[2:]) - 1)
            else:
                if cond[2] == "=":
                    dmin[cond[0]] = max(dmin[cond[0]], int(cond[3:]))
                else:
                    dmin[cond[0]] = max(dmin[cond[0]], int(cond[2:]) + 1)
    result = 1
    for ch in "xmas":
        result *= max(0, dmax[ch] - dmin[ch] + 1)

    ans += result
print(ans)
