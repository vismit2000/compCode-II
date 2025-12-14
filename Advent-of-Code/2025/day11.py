from functools import cache

with open("input.txt") as f:
    lines = f.read().strip().split("\n")
    graph = {line.split(":")[0]: line.split(" ")[1:] for line in lines}

@cache
def total_paths(src, dest, must=frozenset({'dac', 'fft'})):
    must -= {src}
    if src == dest:
        return 1 if not must else 0
    return sum(total_paths(nbr, dest, must) for nbr in graph.get(src, []))

print(total_paths("you", "out", must=frozenset({})))
print(total_paths("svr", "out"))

# Alternative approach
@cache
def count(here, dest):
    return here == dest or sum(count(next, dest) for next in graph.get(here, []))

print(count('you', 'out'))
print(count('svr', 'dac') * count('dac', 'fft') * count('fft', 'out')
    + count('svr', 'fft') * count('fft', 'dac') * count('dac', 'out'))