"""
Writing Parsers and Compilers with PLY: https://www.dabeaz.com/ply/PLYTalk.pdf
Idea taken from https://www.michaelfogleman.com/aoc18/#20 - lexer and parser (using the awesome ply library).
"""

import ply.lex as lex
import ply.yacc as yacc

dirs = {"N": (0, -1), "S": (0, 1), "E": (1, 0), "W": (-1, 0)}

# lexer rules
tokens = ["LPAREN", "RPAREN", "OR", "DIR"]
t_LPAREN = r"\("
t_RPAREN = r"\)"
t_OR = r"\|"
t_DIR = r"[NESW]+"

# Grammar
# pattern : pattern OR concat | concat
# concat : concat term | term
# term : LPAREN pattern RPAREN | DIR | empty


# parser rules
def p_pattern(t):
    "pattern : concat"
    t[0] = t[1]


def p_pattern_or(t):
    "pattern : pattern OR concat"
    t[0] = ("or", t[1], t[3])


def p_concat(t):
    "concat : term"
    t[0] = t[1]


def p_concat_term(t):
    "concat : concat term"
    t[0] = ("concat", t[1], t[2])


def p_term(t):
    "term : DIR"
    t[0] = ("dir", t[1])


def p_term_empty(t):
    "term :"
    t[0] = ("dir", "")


def p_term_paren(t):
    "term : LPAREN pattern RPAREN"
    t[0] = t[2]


# build lexer and parser given above rules
lexer = lex.lex(errorlog=lex.NullLogger())
parser = yacc.yacc(debug=False, write_tables=False, errorlog=yacc.NullLogger())


def parse(text):
    text = text.strip().replace("^", "").replace("$", "")
    return parser.parse(text, lexer=lexer)


def visit(node, doors, points):
    if node[0] == "concat":
        points = visit(node[1], doors, points)
        points = visit(node[2], doors, points)
        return points
    elif node[0] == "or":
        a = visit(node[1], doors, points)
        b = visit(node[2], doors, points)
        return list(set(a) | set(b))
    else:  # dir
        for d in node[1]:
            dx, dy = dirs[d]
            doors |= set((x, y, x + dx, y + dy) for x, y in points)
            doors |= set((x + dx, y + dy, x, y) for x, y in points)
            points = [(x + dx, y + dy) for x, y in points]
        return points


def locate_doors(text):
    doors = set()
    visit(parse(text), doors, [(0, 0)])
    return doors


def search(doors):
    distances = {}
    queue = [(0, 0, 0)]
    while queue:
        x, y, d = queue.pop()
        if (x, y) in distances and distances.get((x, y)) <= d:
            continue
        distances[(x, y)] = d
        for dx, dy in dirs.values():
            if (x, y, x + dx, y + dy) in doors:
                queue.append((x + dx, y + dy, d + 1))
    return distances


content = open("input.txt", "r").read()
doors = locate_doors(content)
distances = search(doors)
print(max(distances.values()))
print(sum(x >= 1000 for x in distances.values()))
