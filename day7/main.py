#!/usr/bin/env python3

with open("input.txt", "r") as f:
	f = [x for x in f.read().split("\n") if x != '']

bags = {}
for line in f:
	name, contains = [x.strip() for x in line.replace("bags", "bag").split("contain")]
	contains = [x.strip() for x in contains.replace(".", "").split(",")]

	if contains == ["no other bag"]:
		contains = []

	for i, bag in enumerate(contains):
		num, id = bag.split(maxsplit = 1)
		num = int(num)

		contains[i] = (num, id)

	bags[name] = contains


def find_gold(starting_bag):
	for num, bag in bags[starting_bag]:
		if bag == "shiny gold bag":
			return 1

		elif find_gold(bag):
			return 1

	return 0

count = 0
for name in bags.keys():
	count += find_gold(name)

print(count)


def part2(starting_bag):
	count = 0

	for num, bag in bags[starting_bag]:
		count += num * (1 + part2(bag))

	return count

print(part2("shiny gold bag"))

