"""
(Simulation) There are N coupons numbered 1 to N in a bag. Draw one after another with replacement. What is the expected number of drawings until the first time a duplication occurs.
"""

import random


def run_simulation(N=100):
    num_trials = 10000
    total_draws = 0
    for _ in range(num_trials):
        coupons = set()
        draws = 0
        while True:
            draws += 1
            draw = random.randint(1, N)
            if draw in coupons:
                break
            coupons.add(draw)
        total_draws += draws
    return total_draws / num_trials


if __name__ == "__main__":
    for N in (1, 5, 10, 100, 1000):
        simulated_value = run_simulation(N)
        actual_value = 0
        for k in range(N + 1):
            temp = 1
            for j in range(k):
                temp *= (N - j) / N
            actual_value += temp
        print(
            f"Actual value: {actual_value:.2f}, Simulated value: {simulated_value:.2f}",
            f"Percentage difference: {(100 * (simulated_value - actual_value) / actual_value):.2f}%",
        )


"""
Actual value: 2.00, Simulated value: 2.00 Percentage difference: 0.00%
Actual value: 3.51, Simulated value: 3.50 Percentage difference: -0.30%
Actual value: 4.66, Simulated value: 4.69 Percentage difference: 0.61%
Actual value: 13.21, Simulated value: 13.15 Percentage difference: -0.46%
Actual value: 40.30, Simulated value: 40.16 Percentage difference: -0.35%
"""
