#!/usr/bin/env python3

with open("input.txt", "r") as f:
	code = [(x.split()[0], int(x.split()[1])) for x in f.read().splitlines()]


def run(code):
	previous_pcs = set()

	acc = 0
	pc = 0

	while pc != len(code):
		if pc in previous_pcs:
			return acc, False # we've been here before

		previous_pcs.add(pc)

		instr, arg = code[pc]

		if instr == "acc":
			acc += arg

		elif instr == "jmp":
			pc += arg - 1

		pc += 1

	return acc, True # halted normally

def patch(code):
	for i, (instr, arg) in enumerate(code):
		orig = (instr, arg)

		code[i] = {
			"jmp": ("nop", arg),
			"nop": ("jmp", arg),
			"acc": orig,
		} [instr]

		res, ok = run(code)

		if ok:
			return res

		code[i] = orig

print(run(code)[0])
print(patch(code))
