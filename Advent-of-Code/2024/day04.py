with open("input.txt", "r") as file:
    lines = file.read().strip().split("\n")
    grid = [list(line) for line in lines]


def count_xmas_occurrences(grid, word="XMAS"):
    rows, cols = len(grid), len(grid[0])
    word_len = len(word)

    def is_valid(x, y):
        return 0 <= x < rows and 0 <= y < cols

    def search_from(x, y, dx, dy):
        for i in range(word_len):
            nx, ny = x + i * dx, y + i * dy
            if not is_valid(nx, ny) or grid[nx][ny] != word[i]:
                return False
        return True

    count1, count2 = 0, 0
    for i in range(rows):
        for j in range(cols):
            for dx in (-1, 0, 1):
                for dy in (-1, 0, 1):
                    if dx == 0 and dy == 0:
                        continue
                    if search_from(i, j, dx, dy):
                        count1 += 1

    for i in range(1, rows - 1):
        for j in range(1, cols - 1):
            if grid[i][j] == "A":
                if f"{grid[i-1][j-1]}{grid[i+1][j+1]}" in (
                    "MS",
                    "SM",
                ) and f"{grid[i-1][j+1]}{grid[i+1][j-1]}" in ("MS", "SM"):
                    count2 += 1

    return count1, count2


print(count_xmas_occurrences(grid))