#!/usr/bin/env python3

with open("input.txt", "r") as f:
	all_groups = [x.strip().split("\n") for x in f.read().split("\n\n")]

anyone = 0
everyone = 0

for group in all_groups:
	all = set(group[0])
	any = set(group[0])

	for person in group[1:]:
		all = all.intersection(person)
		any.update(*person)

	everyone += len(all)
	anyone += len(any)

print(f"part 1: ", anyone)
print(f"part 2: ", everyone)
