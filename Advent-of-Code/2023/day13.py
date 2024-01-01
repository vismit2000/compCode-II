content = open("input.txt", "r").read()
lines = content.split("\n")
n, m = len(lines), len(lines[0])


def gen_matrices(matrix):
    matrices = []
    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            new_matrix = [row[:] for row in matrix]
            new_matrix[i][j] = "#" if new_matrix[i][j] == "." else "."
            matrices.append(new_matrix)
    return matrices


matrices = []
matrix = []
for line in lines:
    if line == "":
        matrices.append(matrix)
        matrix = []
    else:
        matrix.append(list(line))
matrices.append(matrix)

ans = 0

reflections = []
for new_matrix in matrices:
    for rep in range(2):
        n, m = len(new_matrix), len(new_matrix[0])
        for i in range(1, n):
            if 2 * i < n:
                if new_matrix[0:i] == new_matrix[i : 2 * i][::-1]:
                    # ans += 100 * i if rep == 0 else i
                    reflections.append((i, rep))

            else:
                if new_matrix[2 * i - n : i] == new_matrix[i:n][::-1]:
                    # ans += 100 * i if rep == 0 else i
                    reflections.append((i, rep))

        new_matrix = [list(row) for row in zip(*new_matrix)]


for idx, matrix in enumerate(matrices):
    new_matrices = gen_matrices(matrix)
    flag = False
    for new_matrix in new_matrices:
        for rep in range(2):
            n, m = len(new_matrix), len(new_matrix[0])
            for i in range(1, n):
                if reflections[idx] != (i, rep):
                    if 2 * i < n:
                        if new_matrix[0:i] == new_matrix[i : 2 * i][::-1]:
                            ans += 100 * i if rep == 0 else i
                            # print(i, rep)
                            flag = True
                    else:
                        if new_matrix[2 * i - n : i] == new_matrix[i:n][::-1]:
                            ans += 100 * i if rep == 0 else i
                            # print(i, rep)
                            # for row in new_matrix:
                            #     print("".join(row))
                            flag = True
            new_matrix = [list(row) for row in zip(*new_matrix)]
        if flag:
            break
print(ans)
