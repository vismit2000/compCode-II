with open("input.txt", "r") as file:
    lines = file.read().strip().split("\n")
    reports = [list(map(int, line.split())) for line in lines]


def is_valid_sequence(report):
    differences = [report[i] - report[i - 1] for i in range(1, len(report))]
    return all(1 <= d <= 3 for d in differences) or all(
        -3 <= d <= -1 for d in differences
    )


def count_valid_reports(reports):
    valid_count1, valid_count2 = 0, 0
    for report in reports:
        if is_valid_sequence(report):
            valid_count1 += 1
        if any(
            is_valid_sequence(report[:i] + report[i + 1 :]) for i in range(len(report))
        ):
            valid_count2 += 1
    return valid_count1, valid_count2


valid_reports_count = count_valid_reports(reports)
print(valid_reports_count)