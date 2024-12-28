from collections import defaultdict, deque

with open("input.txt", "r") as file:
    lines = file.read().strip().split("\n")
    secrets = tuple(map(int, lines))


def nth_secret(secret: int, n=2000) -> int:
    for _ in range(n):
        secret ^= (secret * 64) % 16777216
        secret ^= (secret // 32) % 16777216
        secret ^= (secret * 2048) % 16777216
    return secret


print(sum(map(nth_secret, secrets)))


def price_timeline(secret, n=2000):
    """Each {delta-4-tuple: price} in the timeline of this secret number for `n` steps."""
    timeline = {}
    deltas = deque(maxlen=4)
    price = secret % 10  # Initial price
    for _ in range(n):
        secret = nth_secret(secret, 1)
        price, previous_price = secret % 10, price
        deltas.append(price - previous_price)
        D = tuple(deltas)
        if len(D) == 4 and D not in timeline:
            timeline[D] = price
    return timeline


def total_bananas(secrets, n=2000):
    """Pairs of {delta-4-tuple: total_bananas_gained} over all secret numbers, for the first `n` 4-tuples of deltas."""
    bananas = defaultdict(int)
    for secret in secrets:
        for deltas, price in price_timeline(secret, n).items():
            bananas[deltas] += price
    return bananas


print(max(total_bananas(secrets).values()))
