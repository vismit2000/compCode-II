with open("input.txt") as f:
    banks = f.read().strip().split("\n")

def joltage(bank, k=2):
    lighted = []
    for battery in bank:
        lighted.append(battery)
        if len(lighted) > k:
            for i in range(len(lighted) - 1):
                if lighted[i] < lighted[i+1]:
                    lighted.pop(i)
                    break
        lighted = lighted[:k]
    return int("".join(lighted))

print(sum(joltage(bank, 12) for bank in banks))