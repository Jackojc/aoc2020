#!/usr/bin/env python3

import sys
import copy


def list_compare(a, b):
    if type(a) != type(b):
        return False
    if type(a) != list:
        return a == b
    if len(a) != len(b):
        return False
    for a_, b_ in zip(a, b):
        if not list_compare(a_, b_):
            return False
    return True


with open(sys.argv[1], "r") as f:
	f = f.read().splitlines()

grid = []

grid.append(['.'] * (len(f[0]) + 2))

for line in f:
	grid.append(['.'] + [x for x in line] + ['.'])


grid.append(['.'] * (len(f[0]) + 2))

initial_state = copy.deepcopy(grid)



def update_grid(grid):
	out_grid = copy.deepcopy(grid)

	for yi, y in enumerate(grid):
		for xi, x in enumerate(y):
			if x == 'L':
				if all([
					grid[yi - 1][xi - 1] != '#',
					grid[yi - 1][xi + 0] != '#',
					grid[yi - 1][xi + 1] != '#',

					grid[yi + 0][xi - 1] != '#',
					grid[yi + 0][xi + 1] != '#',

					grid[yi + 1][xi - 1] != '#',
					grid[yi + 1][xi + 0] != '#',
					grid[yi + 1][xi + 1] != '#'
				]):
					out_grid[yi][xi] = '#'

			elif x == '#':
				if sum([
					1 if grid[yi - 1][xi - 1] == '#' else 0,
					1 if grid[yi - 1][xi + 0] == '#' else 0,
					1 if grid[yi - 1][xi + 1] == '#' else 0,

					1 if grid[yi + 0][xi - 1] == '#' else 0,
					1 if grid[yi + 0][xi + 1] == '#' else 0,

					1 if grid[yi + 1][xi - 1] == '#' else 0,
					1 if grid[yi + 1][xi + 0] == '#' else 0,
					1 if grid[yi + 1][xi + 1] == '#' else 0
				]) >= 4:
					out_grid[yi][xi] = 'L'

	if list_compare(out_grid, grid):
		return False, out_grid

	return True, out_grid



running = True
while running:
	running, grid = update_grid(grid)


count = 0
for y in grid:
	for x in y:
		if x == '#':
			count += 1

print(count)




def cast_ray(incr_x, incr_y, x, y, grid):
	x += incr_x
	y += incr_y

	while x >= 0 and x < len(grid[0]) and y >= 0 and y < len(grid):
		if grid[y][x] == '#':
			return 1

		elif grid[y][x] == 'L':
			return 0

		x += incr_x
		y += incr_y

	return 0


def update_grid2(grid):
	out_grid = copy.deepcopy(grid)

	for yi, y in enumerate(grid):
		for xi, x in enumerate(y):
			if x == 'L':
				if sum([
					cast_ray(-1, -1, xi, yi, grid),
					cast_ray(-1, +0, xi, yi, grid),
					cast_ray(-1, +1, xi, yi, grid),

					cast_ray(+0, -1, xi, yi, grid),
					cast_ray(+0, +1, xi, yi, grid),

					cast_ray(+1, -1, xi, yi, grid),
					cast_ray(+1, +0, xi, yi, grid),
					cast_ray(+1, +1, xi, yi, grid)
				]) == 0:
					out_grid[yi][xi] = '#'

			elif x == '#':
				if sum([
					cast_ray(-1, -1, xi, yi, grid),
					cast_ray(-1, +0, xi, yi, grid),
					cast_ray(-1, +1, xi, yi, grid),

					cast_ray(+0, -1, xi, yi, grid),
					cast_ray(+0, +1, xi, yi, grid),

					cast_ray(+1, -1, xi, yi, grid),
					cast_ray(+1, +0, xi, yi, grid),
					cast_ray(+1, +1, xi, yi, grid)
				]) >= 5:
					out_grid[yi][xi] = 'L'

	if list_compare(out_grid, grid):
		return False, out_grid

	return True, out_grid


grid = initial_state

running = True
while running:
	running, grid = update_grid2(grid)


count = 0
for y in grid:
	for x in y:
		if x == '#':
			count += 1

print(count)



