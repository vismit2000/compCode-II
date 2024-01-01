content = open("input.txt", "r").read()
lines = content.split("\n")

d = {}

ans = 0
for i, line in enumerate(lines):
    d[i + 1] = d.get(i + 1, 0) + 1
    winning, having = line.split(": ")[1].split(" | ")
    winning = winning.split(" ")
    having = having.split(" ")
    wins = 0
    for card in having:
        if card != "" and card in winning:
            wins += 1

    ans += int(pow(2, wins - 1))
    for j in range(i + 2, i + 2 + wins):
        d[j] = d.get(j, 0) + d[i+1]

print(ans)
print(sum(d.values()))