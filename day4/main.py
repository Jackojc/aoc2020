#!/usr/bin/env python3

with open("input.txt", "r") as f:
	string = f.read()

passports = [x.replace("\n", " ").split() for x in string.split("\n\n")]
passports = [x for x in passports if x != []]

new_passports = []

for x in passports:
	v = {}
	for field in x:
		k, val = field.split(":")
		v[k] = val

	new_passports.append(v)

valid = 0
for passport in new_passports:
	if (
		"byr" in passport and
		"iyr" in passport and
		"eyr" in passport and
		"hgt" in passport and
		"hcl" in passport and
		"ecl" in passport and
		"pid" in passport
	):
		if not(1920 <= int(passport["byr"]) <= 2002):
			continue

		if not(2010 <= int(passport["iyr"]) <= 2020):
			continue

		if not(2020 <= int(passport["eyr"]) <= 2030):
			continue

		if "cm" in passport["hgt"]:
			if not(150 <= int(passport["hgt"][:-2]) <= 193):
				continue

		elif "in" in passport["hgt"]:
			if not(59 <= int(passport["hgt"][:-2]) <= 76):
				continue

		else:
			continue

		if passport["ecl"] not in ["amb", "blu", "brn" , "gry" , "grn" , "hzl" , "oth"]:
			continue

		if passport["hcl"][0] != "#" or len(passport["hcl"]) != 7 or any(x not in "0123456789abcdef" for x in passport["hcl"][1:]):
			continue

		if len(passport["pid"]) != 9 or any(x not in "0123456789" for x in passport["pid"]):
			continue

		valid += 1

print(valid)
