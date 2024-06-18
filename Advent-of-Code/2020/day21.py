# another Sudoku-like problem - use of eliminate_others

from collections import namedtuple
from itertools import chain

flatten = chain.from_iterable

content = open("input.txt", "r").read()

Food = namedtuple("Food", "I, A")  # I for set of ingredients; A for set of allergens


def parse_food(line) -> Food:
    "Parse 'xtc wkrp (contains fish, nuts)' => Food({'xtc', 'wkrp'}, {'fish', 'nuts'})"
    ingredients, allergens = line.split(" (contains ")
    return Food(set(ingredients.split(" ")), set(allergens[:-1].split(", ")))


foods = [parse_food(line) for line in content.splitlines()]


def eliminate_others(possible, i):
    "Eliminate possible[i] from all other possible[j]."
    for j in possible:
        if j != i:
            possible[j] -= possible[i]


def bad_ingredients(foods) -> dict[str, set[str]]:
    "A dict of {allergen: {set_of_ingredients_it_could_be}}; each set should have len 1."
    all_ingredients = set(flatten(food.I for food in foods))
    all_allergens = set(flatten(food.A for food in foods))
    possible = {a: set(all_ingredients) for a in all_allergens}
    while any(len(possible[a]) > 1 for a in possible):
        for food in foods:
            for a in food.A:
                possible[a] &= food.I
                if len(possible[a]) == 1:
                    eliminate_others(possible, a)
    return possible


def day21_1(foods):
    "How many times does an ingredient with an allergen appear?"
    bad = bad_ingredients(foods)
    allergens = set(flatten(bad.values()))
    return sum(len(food.I - allergens) for food in foods)


def day21_2(foods) -> str:
    "What are the bad ingredients, sorted by the allergen name that contains them?"
    bad = bad_ingredients(foods)
    return ",".join(next(iter(bad[a])) for a in sorted(bad))


print(day21_1(foods))
print(day21_2(foods))
