import random
import os
import datetime
import numpy as np

TASK_NUM = 1

N_LIMIT = 5000

def log(string):
	print(string, flush = True)
	with open("gen.log", "a") as f:
		f.write(f"[{datetime.datetime.now()}] {string}\n")

def transform(s: str):
	return s.translate(str.maketrans({"0": "v", "1": "^"}))

def flip(s: str):
	return s.translate({48: 49, 49: 48})

def getRandomString(length, prob_0 = 0.5):
	rng = np.random.default_rng()
	return "".join(map(str, rng.choice(2, size = length, p = [prob_0, 1 - prob_0])))

def appendStrictOneSide(s, max_length = 10, prob_append = 1, prob_left = 0.5, prob_0 = 0.5, **extra_param):
	rng = np.random.default_rng()
	if rng.random() < prob_append:
		if rng.random() < prob_left:
			return getRandomString(rng.integers(max_length, endpoint = True), prob_0 = prob_0) + s
		else:
			return s + getRandomString(rng.integers(max_length, endpoint = True), prob_0 = prob_0)
	return s

def appendGeneral(s, max_length = 10, prob_append = 1, prob_left = 0.5, prob_right = 0.5, prob_0 = 0.5, **extra_param):
	rng = np.random.default_rng()
	if rng.random() < prob_append:
		if rng.random() < prob_left:
			s = getRandomString(rng.integers(max_length, endpoint = True), prob_0 = prob_0) + s
		if rng.random() < prob_right:
			s += getRandomString(rng.integers(max_length, endpoint = True), prob_0 = prob_0)
	return s

def genUniform(n, **extra_param):
	return transform("".join(random.choices("01", k = n)))

def genUnbalanced(n, prob_0 = 0.5, **extra_param):
	rng = np.random.default_rng()
	return transform("".join(map(str, rng.choice(2, size = n, p = [prob_0, 1 - prob_0]))))

def genLongSuccession(n, max_length = 10, longer_succession = False, **extra_param):
	rng = np.random.default_rng()
	s = ""
	digit = rng.integers(2)
	while len(s) < n:
		delta = rng.integers(1, max_length, endpoint = True)
		if delta > n - len(s):
			delta = n - len(s)
		s += f"{digit:1d}" * delta
		if longer_succession:
			digit = rng.integers(2)
		else:
			digit = 1 - digit

	return transform(s)

def genRatherSymmetric(n, init_seq = "", append_sides = None, **extra_param):
	rng = np.random.default_rng()
	s = init_seq
	while len(s) < n:
		s = s + f"{rng.integers(2):1d}" + flip(s)[::-1]
		if append_sides is not None:
			s = append_sides(s, **extra_param)
	
	start = rng.integers(len(s) - n, endpoint = True)

	return transform(s[start : start + n])

def genTestcase(filename, n, gen, **extra_param):
	log(f"Generating input for case {filename}, params: {n = }, {gen.__name__}, {extra_param = }")
	# assert ..., "Parameters invalid!"
	assert 1 <= n <= N_LIMIT

	s = gen(n, **extra_param)
	assert len(s) == n

	with open(f"{filename}.in", "w") as f:
		print(n, file = f)
		print(s, file = f)

	log(f"Generating output for case {filename}")
	os.system(f'(time {os.path.join("..", "Wonderseabreeze", "std")} < {filename}.in > {filename}.ans) 2>> gen.log')		# Linux
	# os.system(f'({os.path.join("..", "Wonderseabreeze", "std")} < {filename}.in > {filename}.ans) 2>> gen.log')				# Windows

class Cases:
	def __init__(self, prefix = ""):
		self.cnt = 0
		self.prefix = prefix
	
	def gen(self, n, gen, **extra_param):
		self.cnt += 1
		genTestcase(f"{self.prefix}{self.cnt}", n, gen, **extra_param)
	
	def skip(self, cnt = 1):
		self.cnt += cnt

os.system("rm gen.log")
testcase = Cases()
# precase = Cases("../pre/")
# sample = Cases("../down/")

for i in range(1, TASK_NUM + 1):
	log(f"Generating subtask {i}")
	pre = testcase.cnt
	# pre_pre = precase.cnt
	# add testcases below

	rng = np.random.default_rng()
	
	testcase.gen(N_LIMIT, genUnbalanced, prob_0 = 0)
	testcase.gen(N_LIMIT, genUnbalanced, prob_0 = 1)

	for cnt in range(4):
		testcase.gen(N_LIMIT, genUniform)
	
	for prob_0 in (0.1, 0.3, 0.7, 0.9):
		testcase.gen(N_LIMIT, genUnbalanced, prob_0 = prob_0)
		testcase.gen(N_LIMIT - rng.integers(10), genUnbalanced, prob_0 = prob_0)
	
	for cnt in range(2):
		testcase.gen(N_LIMIT - rng.integers(10), genLongSuccession)
	for cnt in range(2):
		testcase.gen(N_LIMIT - rng.integers(10), genLongSuccession)
	
	for cnt in range(2):
		testcase.gen(N_LIMIT, genRatherSymmetric)
	for cnt in range(2):
		testcase.gen(4095, genRatherSymmetric)

	# 22

	testcase.gen(N_LIMIT - rng.integers(10), genRatherSymmetric, append_sides = appendStrictOneSide, prob_append = 2 / 3)
	testcase.gen(N_LIMIT - rng.integers(10), genRatherSymmetric, append_sides = appendStrictOneSide, max_length = 3, prob_append = 0.2)
	for cnt in range(2):
		testcase.gen(N_LIMIT - rng.integers(10), genRatherSymmetric, append_sides = appendStrictOneSide, prob_append = 0.75, prob_left = 1)
	for cnt in range(2):
		testcase.gen(N_LIMIT - rng.integers(10), genRatherSymmetric, append_sides = appendStrictOneSide, prob_append = 0.75, prob_left = 0)
	
	for cnt in range(2):
		testcase.gen(N_LIMIT - rng.integers(10), genRatherSymmetric, appensides = appendGeneral)
	for cnt in range(2):
		testcase.gen(N_LIMIT - rng.integers(10), genRatherSymmetric, appensides = appendGeneral, max_length = 3, prob_append = 0.5)
	for cnt in range(2):
		testcase.gen(N_LIMIT - rng.integers(10), genRatherSymmetric, appensides = appendGeneral, max_length = 7, prob_left = 0.8, prob_right = 0.1)
	for cnt in range(2):
		testcase.gen(N_LIMIT - rng.integers(10), genRatherSymmetric, appensides = appendGeneral, max_length = 7, prob_left = 0.1, prob_right = 0.8)

	
	# add testcases above		
	log(f"Subtask {i} done. ({pre + 1} - {testcase.cnt})")
	# log("Subtask {} done. (test: {} - {}; pre: {} - {})".format(i, pre + 1, testcase.cnt, pre_pre + 1, precase.cnt))

# for duck
# os.system("mkdir download")
# os.system("cp ../down/* ./download/")
