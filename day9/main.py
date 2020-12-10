#!/usr/bin/env python3

with open("input.txt", "r") as f:
	lines = [int(x) for x in f.read().splitlines()]

def part1(lines, preamble = 25):
	for i, line in enumerate(lines[preamble:], preamble):
		possible = lines[i - preamble : i]

		for a in possible:
			for b in possible:
				if a + b == line:
					break
			else:
				continue

			break

		else:
			return line

def part2(lines, target):
	for i, current in enumerate(lines):
		sum = 0

		for j in range(i + 1, len(lines)):
			if sum == target:
				group = lines[i : j - 1]
				return min(group) + max(group)

			if sum > target:
				break

			sum += lines[j]
			j += 1

print(num := part1(lines))
print(part2(lines, num))
