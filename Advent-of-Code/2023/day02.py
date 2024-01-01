content = open("input.txt", "r").read()
lines = content.split("\n")

from functools import reduce

allowed = {
    "red": 12,
    "green": 13,
    "blue": 14,
}

ans = 0
for line in lines:
    game, info = line.split(": ")
    game_id = int(game.split(" ")[1])
    combs = info.split("; ")
    # flag = True
    d = {
        "red": 0,
        "green": 0,
        "blue": 0,
    }

    for comb in combs:
        # d = {}
        colors = comb.split(", ")
        for color in colors:
            qty, name = color.split(" ")
            # d[name] = int(qty)
            qty = int(qty)
            d[name] = max(d[name], qty)
        #     if d[name] > allowed[name]:
        #         flag = False
        #         break
        # if flag is False:
        #     break
    ans += reduce(lambda x, y: x*y, d.values())

    # if flag:
    #     ans += game_id
print(ans)