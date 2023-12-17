import numpy as np

def genMatrix(x0, y0, pattern: np.ndarray, height = 5, width = 5):
	mat = np.zeros((5, 5), dtype = np.int32)
	mat[x0 : x0 + pattern.shape[0], y0 : y0 + pattern.shape[1]] = pattern
	lines = ["".join(map(str, row)) for row in mat]
	return "\n".join(lines).translate(str.maketrans({"0": ".", "1": "o"}))

def genInputOutput(caseid, matrices, answers):
	assert len(matrices) == len(answers)
	
	rng = np.random.default_rng()
	indices = rng.permutation(len(matrices))
	matrices = [matrices[i] for i in indices]
	answers = [answers[i] for i in indices]

	with open(f"{caseid}.in", "w") as fin:
		print(len(matrices), file = fin)
		for matrix in matrices:
			print(matrix, file = fin)
	with open(f"{caseid}.ans", "w") as fans:
		for answer in answers:
			print("Far" if answer else "Away", file = fans)
	return

if __name__ == "__main__":
	patterns = [
		np.ones((1, 1), dtype = np.int32),
		np.ones((1, 2), dtype = np.int32),
		np.ones((1, 3), dtype = np.int32),
		np.array([[1, 1], [1, 0]], dtype = np.int32),
		np.ones((1, 4), dtype = np.int32),
		np.ones((2, 2), dtype = np.int32),
		np.array([[1, 1, 1], [1, 0, 0]], dtype = np.int32),
		np.array([[1, 1, 1], [0, 1, 0]], dtype = np.int32),
		np.array([[1, 1, 0], [0, 1, 1]], dtype = np.int32)
	]
	rotations = [
		1, 2, 2, 4, 2, 1, 4, 4, 2
	]
	flip = [
		0, 0, 0, 0, 0, 0, 1, 0, 1
	]

	first_win = [
		0, 1, 0, 0, 0, 0, 1, 1, 1
	]
	matrices = []
	answers = []

	matrices4 = []
	answers4 = []

	for i in range(4):
		for j in range(rotations[i]):
			pattern = np.rot90(patterns[i], k = j)
			for x0 in range(5 - pattern.shape[0] + 1):
				for y0 in range(5 - pattern.shape[1] + 1):
					matrices.append(genMatrix(x0, y0, pattern))
					answers.append(first_win[i])
					# if flip

	for i in range(4, 9):
		for j in range(rotations[i]):
			pattern = np.rot90(patterns[i], k = j)
			for x0 in range(5 - pattern.shape[0] + 1):
				for y0 in range(5 - pattern.shape[1] + 1):
					matrices4.append(genMatrix(x0, y0, pattern))
					answers4.append(first_win[i])
					if flip[i]:
						matrices4.append(genMatrix(x0, y0, pattern[:, ::-1]))
						answers4.append(first_win[i])

	print(len(matrices), len(matrices4))

	count4 = len(matrices4)

	rng = np.random.default_rng()
	indices = rng.permutation(len(matrices4))
	matrices4 = [matrices4[i] for i in indices]
	answers4 = [answers4[i] for i in indices]

	for i in range(400 - len(matrices) - count4):
		j = rng.integers(count4)
		matrices4.append(matrices4[j])
		answers4.append(answers4[j])
	
	matrices += matrices4
	answers += answers4

	genInputOutput(1, matrices[:200], answers[:200])
	genInputOutput(2, matrices[200:], answers[200:])
