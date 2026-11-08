import re
ans = 0
for bases, votes in re.findall(r"ISO2?-(\d+) (\d+)", open("../input.txt").read()):
    w = [int(b) ** i for i, b in enumerate((bases[::-1] * len(votes))[:len(votes)])]
    v = sum(int(d) * x for d, x in zip(votes[::-1], w))
    # smallest[val]: smallest number that makes val using the positions seen so far
    smallest = {0: 0}
    for i, x in enumerate(w):
        new = {}
        for val, num in smallest.items():
            for d in range(10):
                t, n = val + d * x, num + d * 10 ** i
                if t <= v:
                    new[t] = min(new.get(t, n), n)
        smallest = new
    ans += v * (smallest[v] == int(votes))
print(ans)
