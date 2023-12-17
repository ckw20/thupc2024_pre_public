import os
import yaml

def check(expression, log, *ref):
	if not expression:
		if ref:
			print(f"Check failed: {log} {ref}.")
		else:
			print(f"Check failed: {log}.")
		return False
	return True

def check_integer_bounded(var, lbd, rbd, var_name = "number", *ref):
	return check(lbd <= var <= rbd, f"{var_name} out of range", (lbd, rbd, var) + ref)

def read_line(file, num):
	line = file.readline()
	if line[-1] == "\n":
		line = line[:-1]
	assert line.count(" ") == num - 1
	numbers = line.split(" ")
	for number in numbers:
		assert number.isdigit()
	return list(map(int, line.split()))

def validate(filename):
	print(f"Checking case {filename}:")
	flag = True
	with open(filename, "r") as f:
		n, q, s = read_line(f, 3)
		flag &= check_integer_bounded(n, 2, 301, "N")
		flag &= check_integer_bounded(q, 1, 600, "Q")
		flag &= check_integer_bounded(s, 1, n, "S")

		fa = [0, 0] + read_line(f, n - 1)
		counts = [0] * (n + 1)
		for i in range(2, n + 1):
			flag &= check_integer_bounded(fa[i], 1, i - 1, f"fa[{i}]")
			counts[fa[i]] += 1
			flag &= check_integer_bounded(counts[fa[i]], 0, 2, f"counts[{fa[i]}]", f"@{i}")

		r = [0, 0] + read_line(f, n - 1)
		for i in range(2, n + 1):
			flag &= check_integer_bounded(r[i], 0, 1000000000, f"r[{i}]")
		
		p = [0, 0] + read_line(f, n - 1)
		for i in range(2, n + 1):
			flag &= check_integer_bounded(p[i], 0, 1000000000, f"p[{i}]")
		
		for i in range(1, n + 1):
			flag &= check_integer_bounded(read_line(f, 1)[0], 1, 4, f"op[{i}]")
	
	return flag

if __name__ == "__main__":
	with open("../../conf.yaml", "r", encoding = "utf-8") as f:
		config = yaml.load(f, yaml.FullLoader)
		data = config["data"][0]["cases"]
		sample = config["samples"][0]["cases"]
	
	passed = 0
	for case in data:
		passed += validate(os.path.join('..', '..', 'data', f"{case}.in"))
	print(f"Data: {passed}/{len(data)} OK.")

	passed = 0
	for case in sample:
		passed += validate(os.path.join('..', '..', 'down', f"{case}.in"))
	print(f"Sample: {passed}/{len(sample)} OK.")