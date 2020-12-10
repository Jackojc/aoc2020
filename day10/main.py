#!/usr/bin/env python3

import collections
from functools import reduce
import operator

with open("input.txt", "r") as f:
	adapters = [int(x) for x in f.read().splitlines()]

def find_adapter(num, adapters):
	check = ((x in adapters, x) for x in [num + 1, num + 2, num + 3])

	for i, (contained, x) in enumerate(check):
		if contained:
			return (i + 1, x)

	return None

current_adapter = 0
final_rating = 0

diffs = [3] # final adapter has a diff of 3

while out := find_adapter(current_adapter, adapters):
	diff, adapter = out
	diffs.append(diff)

	current_adapter = adapter
	final_rating = current_adapter + 3


occurences = collections.Counter(diffs)
# print(final_rating)
# print(occurences)
# print(reduce(operator.mul, occurences.values(), 1))





adapters.sort()

combinations = {0 : 1}

for adapter in adapters:
	combinations[adapter] = combinations.get(adapter - 1, 0) + combinations.get(adapter - 2, 0) + combinations.get(adapter - 3, 0)

print(combinations[adapters[-1]])
