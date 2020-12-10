#!/usr/bin/env python3

from collections import defaultdict

class ProgramTree:

	def __init__(self, line, inst, arg):
		self.line = line
		self.inst = inst
		self.arg = arg
		self.next = line + (arg if inst == "jmp" else 1)
		self.prev = []

	def __hash__(self):
		return hash((self.line, self.inst))

insts = None
with open("input.txt") as f:
	insts = f.read().splitlines()

trees = [None] * len(insts)
for j in range(len(insts), 0, -1):
	i, a = insts[j-1].split()
	t = ProgramTree(j, i, int(a))
	trees[j-1] = t

for t in trees:
	if t.next-1 < len(trees):
		trees[t.next-1].prev.append(t)

ends = [False] * len(trees)
def set_ending_paths(t: ProgramTree):
	ends[t.line-1] = True
	for tt in t.prev:
		set_ending_paths(tt)

set_ending_paths(t)

visited = [False] * len(trees)
j = 0
acc = 0
while j < len(trees) and not visited[j]:
	visited[j] = True
	t = trees[j]
	j = trees[j].next-1

	if t.inst == "acc":
		acc += t.arg

# comment next two loops for only part 1
for j in range(len(trees)):
	if not visited[j]:
		continue

	t = trees[j]
	if t.inst == "nop":
		if ends[(t.line-1) + t.arg]:
			t.inst = "jmp"
			t.next = t.line + t.arg
	elif t.inst == "jmp":
		if ends[t.line]:
			t.inst = "nop"
			t.next = t.line+1

# run program
j = 0
acc = 0
while j < len(trees):
	t = trees[j]
	j = trees[j].next-1

	if t.inst == "acc":
		acc += t.arg

print(acc)

