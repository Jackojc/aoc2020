from collections import defaultdict, Counter

x, y = 0, 0
wx, wy = 10, 1
with open("test.txt") as f:
	for l in f:
		if l[0] == "L":
			k = int(l[1:])//90
			if k == 1:
				wx, wy = -wy, wx
			if k == 2:
				wx, wy = -wx, -wy
			if k == 3:
				wx, wy = wy, -wx
		elif l[0] == "R":
			k = int(l[1:])//90
			if k == 1:
				wx, wy = wy, -wx
			if k == 2:
				wx, wy = -wx, -wy
			if k == 3:
				wx, wy = -wy, wx
		elif l[0] == "F":
			x, y = x + wx*int(l[1:]), y + wy*int(l[1:])
		elif l[0] == "E":
			wx += int(l[1:])
		elif l[0] == "N":
			wy += int(l[1:])
		elif l[0] == "W":
			wx -= int(l[1:])
		elif l[0] == "S":
			wy -= int(l[1:])

print(abs(x) + abs(y), x, y)

