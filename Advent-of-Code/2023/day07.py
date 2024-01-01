content = open("input.txt", "r").read()
lines = content.split("\n")

from collections import Counter
from functools import cmp_to_key

d = {
    "2": 2,
    "3": 3,
    "4": 4,
    "5": 5,
    "6": 6,
    "7": 7,
    "8": 8,
    "9": 9,
    "T": 10,
    "J": 1,  # 11 for part 1
    "Q": 12,
    "K": 13,
    "A": 14,
}


def compare(card1, card2):
    if len(card1[2]) != len(card2[2]):
        return len(card2[2]) - len(card1[2])
    mx1 = max(card1[2].values())
    mx2 = max(card2[2].values())
    if mx1 != mx2:
        return mx1 - mx2
    for i in range(len(card1[0])):
        if d[card1[0][i]] != d[card2[0][i]]:
            return d[card1[0][i]] - d[card2[0][i]]
    return -1


cards = []
for line in lines:
    hand, bid = line.split(" ")
    cards.append(
        (
            hand,
            int(bid),
            dict(sorted(Counter(hand).items(), key=lambda x: x[1], reverse=True)),
        )
    )

cards2 = []
for hand, bid, dic in cards:
    j_value = 0
    if "J" in dic:
        j_value = dic.pop("J")
    if hand == "JJJJJ":
        dic = {"J": 0}
    fk, _ = next(iter(dic.items()))
    dic[fk] += j_value
    cards2.append((hand, bid, dic))

ranked_cards = sorted(cards2, key=cmp_to_key(compare))
ans = sum([i * card[1] for i, card in enumerate(ranked_cards, 1)])
print(ans)

# 254412181
