#!/usr/bin/env python3

import sys
import math

with open(sys.argv[1], "r") as f:
	instructions = [(x[:1], int(x[1:])) for x in f.read().splitlines()]


heading = 1
x, y = 0, 0

for direction, amount in instructions:
	if direction == "F":
		direction = ["N", "E", "S", "W"][heading]

	heading, x, y = {
		"N": (heading, x, y + amount),
		"S": (heading, x, y - amount),
		"W": (heading, x + amount, y),
		"E": (heading, x - amount, y),
		"L": ((heading - amount // 90) % 4, x, y),
		"R": ((heading + amount // 90) % 4, x, y),
	} [direction]

print(abs(x) + abs(y))


waypoint_x, waypoint_y = 10, 1
ship_x, ship_y = 0, 0

for direction, amount in instructions:
	if direction == "F":
		ship_x += waypoint_x * amount
		ship_y += waypoint_y * amount

	elif direction == "L":
		for _ in range(amount // 90):
			waypoint_x, waypoint_y = -waypoint_y, waypoint_x

	elif direction == "R":
		for _ in range(amount // 90):
			waypoint_x, waypoint_y = waypoint_y, -waypoint_x

	else:
		waypoint_x, waypoint_y = {
			"N": (waypoint_x, waypoint_y + amount),
			"S": (waypoint_x, waypoint_y - amount),
			"W": (waypoint_x - amount, waypoint_y),
			"E": (waypoint_x + amount, waypoint_y),
		} [direction]

print(abs(ship_x) + abs(ship_y))
