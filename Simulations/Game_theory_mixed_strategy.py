"""
(Simulation) (Game theory) There are two cards, an ace and a deuce. Player A draws either of the two at random; B does not see which card is drawn. If A has drawn the ace, he says "I've got the ace" and demands a dollar from his opponent. If A has drawn the deuce, then he may either (A1) say "I've got the ace" and demand a dollar from his opponent or (A2) confess that he has got the deuce and pay his opponent a dollar.
The opponent, if he is paid the dollar voluntarily, can only accept it. If, however, a dollar is demanded from him, then he may either (B1) believe that player A has got the ace and give him the dollar or (B2) demand a check so as to see whether A's statement is true or not. If it is found that A does have the ace, B must pay A two dollars. If, however, it is found that A is bluffing B and has the deuce, player A pays B two dollars.
Analyse the game and find the optimal strategy for each player and the expected payoff.
"""

import random


def simulate_game():
    # Define the cards
    cards = ["ace", "deuce"]

    # Player A draws a card at random
    drawn_card = random.choice(cards)

    # Player A's strategy
    if drawn_card == "ace":
        A_action = "demand"
    else:
        A_action = random.choices(["demand", "confess"], weights=[1 / 3, 2 / 3], k=1)[0]

    # Player B's strategy
    if A_action == "confess":
        B_action = "accept"
    else:
        B_action = random.choices(["believe", "check"], weights=[1 / 3, 2 / 3], k=1)[0]

    # Calculate the payoff
    if A_action == "confess":
        payoff_A = -1
        payoff_B = 1
    elif A_action == "demand" and B_action == "believe":
        payoff_A = 1
        payoff_B = -1
    elif A_action == "demand" and B_action == "check":
        if drawn_card == "ace":
            payoff_A = 2
            payoff_B = -2
        else:
            payoff_A = -2
            payoff_B = 2

    return payoff_A, payoff_B


def run_simulations(num_simulations):
    total_payoff_A = 0
    total_payoff_B = 0

    for _ in range(num_simulations):
        payoff_A, payoff_B = simulate_game()
        total_payoff_A += payoff_A
        total_payoff_B += payoff_B

    expected_payoff_A = total_payoff_A / num_simulations
    expected_payoff_B = total_payoff_B / num_simulations

    return expected_payoff_A, expected_payoff_B


# Run the simulation for a large number of games
num_simulations = 10000
expected_payoff_A, expected_payoff_B = run_simulations(num_simulations)

print(f"Expected payoff for Player A: {expected_payoff_A}")
print(f"Expected payoff for Player B: {expected_payoff_B}")
