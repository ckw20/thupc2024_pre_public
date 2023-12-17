import numpy as np

result = {}
patterns = [
	np.array([[1, 1]]),
	np.array([[1, 1, 1]]),
	np.array([[1, 1], [0, 1]]),
	np.array([[1, 1, 1, 1]]),
	np.array([[1, 1], [1, 1]]),
	np.array([[1, 1, 0], [0, 1, 1]]),
	np.array([[1, 1, 1], [0, 1, 0]]),
	np.array([[1, 1, 1], [1, 0, 0]])
]
pattern = np.zeros((4, 4))
LENGTH = 5

get_result = lambda step: 1 if step % 3 == 0 else -1

def check(state, player):
	global pattern
	# for rot in range(4):
	for i in range(LENGTH + 1 - pattern.shape[0]):
		for j in range(LENGTH + 1 - pattern.shape[1]):
			for x in range(pattern.shape[0]):
				for y in range(pattern.shape[1]):
					if pattern[x, y] and state[i + x, j + y] != player:
						break
				else:
					continue
				break
			else:
				# if pattern.sum() == 3:
					# print(state, player)
				return True
	# pattern = np.rot90(pattern)
	return False

def compress(state):
	return "".join(map(str, state.flatten()))

def Alice(step, state, comp):
	# comp = compress(state)
	if comp in result:
		return result[comp]
	best = -2
	for x in range(LENGTH):
		for y in range(LENGTH):
			if state[x, y] == 0:
				state[x, y] = 1
				if check(state, 1):
					now = get_result(step)
				else:
					now = Bob(step + 1, state, comp + 2 ** (x * 5 + y))
				state[x, y] = 0
				if now == 1:
					result[comp] = 1
					# print(pattern, state, f"({x}, {y})")
					return 1
				if now > best:
					best = now
	result[comp] = best
	return best

def Bob(step, state, comp):
	# comp = compress(state)
	if comp in result:
		return result[comp]
	best = 2
	for x in range(LENGTH):
		for y in range(LENGTH):
			if state[x, y] == 0:
				# state[x, y] = 2
				# if check(state, 2):
				state[x, y] = 1
				if check(state, 1):
					now = -get_result(step)
				else:
					now = Alice(step + 1, state, comp + 2 ** (x * 5 + y))
				state[x, y] = 0
				if now == -1:
					result[comp] = -1
					return -1
				if now < best:
					best = now
	result[comp] = best
	return best



for pattern in patterns:
	state = np.zeros((LENGTH, LENGTH), dtype = np.int32)
	print(pattern, Alice(1, state, 0), flush = True)
	result = {}