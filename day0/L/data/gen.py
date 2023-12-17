import random
import os
import copy
import datetime
import numpy as np
import tqdm

TASK_NUM = 1

N_LIMIT = 500
L_LIMIT = 8
R_LIMIT = 1000
K_LIMIT = 1000
Q_LIMIT = 1000

def log(string):
	print(string, flush = True)
	with open("gen.log", "a") as f:
		f.write("[{}] {}\n".format(datetime.datetime.now(), string))

def getPointByAngles(r, theta, phi):
	return r * np.array([np.sin(theta) * np.cos(phi), np.sin(theta) * np.sin(phi), np.cos(theta)])

def getPointByParameters(r, a, b):
	return getPointByAngles(r, np.pi * a, np.pi * b)

def rotate_y(angle):
	c = np.cos(angle)
	s = np.sin(angle)
	return np.mat([
		[c, 0, s],
		[0, 1, 0],
		[-s, 0, c]
	])

def rotate_z(angle):
	c = np.cos(angle)
	s = np.sin(angle)
	return np.mat([
		[c, -s, 0],
		[s, c, 0],
		[0, 0, 1]
	])

def rotate_to_north(theta, phi):
	return rotate_y(-theta) * rotate_z(-phi)

def rotateByPoint(p):
	r = np.sum(p ** 2) ** 0.5
	theta = np.arccos(p[2] / r)
	phi = np.arctan2(p[1], p[0])
	return rotate_to_north(theta, phi)

def between(o, a, b, c):
	rotate = rotateByPoint(o)
	a = rotate * np.mat(a).reshape(3, 1)
	b = rotate * np.mat(b).reshape(3, 1)
	c = rotate * np.mat(c).reshape(3, 1)
	a = np.arctan2(a[1, 0], a[0, 0])
	b = np.arctan2(b[1, 0], b[0, 0])
	c = np.arctan2(c[1, 0], c[0, 0])
	if c < a:
		c += np.pi * 2
	if c - a > np.pi:
		a, c = c, a + np.pi * 2
		if a > np.pi:
			a -= np.pi * 2
			c -= np.pi * 2
	while b < a:
		b += np.pi * 2
	return a - 1e-6 <= b <= c + 1e-6

def intersect(p1, p2, q1, q2):
	a1 = copy.deepcopy(p1)
	a2 = copy.deepcopy(p2)
	b1 = copy.deepcopy(q1)
	b2 = copy.deepcopy(q2)

	# print(p1, p2, q1, q2, between(a1, b1, a2, b2), between(a2, b1, a1, b2), between(b1, a1, b2, a2), between(b2, a1, b1, a2))

	return between(a1, b1, a2, b2) and between(a2, b1, a1, b2) and between(b1, a1, b2, a2) and between(b2, a1, b1, a2)

def getPointsNorthContentric(n, num_circles = None, perturbation = 3, **extra_param):
	if num_circles is None:
		num_circles = int(n ** 0.5)
	
	rng = np.random.default_rng()
	towers = [(0, 0, np.round(rng.uniform(1, Q_LIMIT), 4))]
	sep = np.linspace(1, n, num_circles + 1).astype(np.int32)
	for i in range(num_circles):
		num_points = sep[i + 1] - sep[i]
		abase = 0.5 / num_circles * (i + 1)
		aseq = (abase + rng.integers(-perturbation, perturbation, num_points, endpoint = True) / 10000.0).round(4)
		assert np.all((aseq >= 0) & (aseq <= 1))
		bseq = np.linspace(0, 2, num_points, endpoint = False).round(4)
		qseq = rng.uniform(1, Q_LIMIT, num_points).round(4)
		towers += list(zip(aseq, bseq, qseq))

	return towers

def genChain(n, m, l = None, **extra_param):
	rng = np.random.default_rng()
	if l is None:
		l = rng.integers(1, L_LIMIT, endpoint = True)
	r = rng.uniform(100, R_LIMIT)
	towers = []
	ratio = rng.uniform(-1, 1)
	for i in range(n):
		towers.append((i / n, ratio * 2 * i / n, rng.uniform(1, Q_LIMIT)))
	return n, n - 1, l, 0, n - 1, r, rng.uniform(1, K_LIMIT), towers, [(i - 1, i) for i in range(1, n)]

def genGrid(n, m, l = None, num_longitudes = None, use_polars = True, perturbation = 3, clumping = 0.5, **extra_param):
	
	rng = np.random.default_rng()
	if l is None:
		l = rng.integers(1, L_LIMIT, endpoint = True)
	if num_longitudes is None:
		num_longitudes = rng.integers(1, n - 2, endpoint = True)
	r = rng.uniform(10, R_LIMIT)

	try_cnt = 0
	while True:
		try_cnt += 1
		print(f"Try {try_cnt}...", flush = True)
		towers = [(1, 0, rng.uniform(1, Q_LIMIT))]
		num_points = rng.multinomial(n - 2 - num_longitudes, np.ones(num_longitudes) / num_longitudes) + 1
		# longitudes = np.sort(rng.choice(2000, num_longitudes, replace = False) / 1000.0)
		splits = np.linspace(0, 20000, num_longitudes + 1).astype(np.int32)
		longitudes = rng.integers(splits[:-1] + perturbation, splits[1:] - perturbation, endpoint = True) / 10000.0
		indices = [np.arange(num_points[:i].sum(), num_points[:i + 1].sum()) + 1 for i in range(num_longitudes)]
		# print(indices)
		edges = []
		for i in range(num_longitudes):
			npi = num_points[i]
			splits = np.linspace(30, 970, npi + 1).astype(np.int32)
			while True:
				aseq = rng.integers(splits[:-1], splits[1:], endpoint = True)[::-1] / 1000.0 + rng.integers(-perturbation, perturbation, npi) / 10000.0
				if npi == 1 or np.min(aseq[:-1] - aseq[1:]) >= 0.01:
					break
			towers += list(zip(aseq, longitudes[i] + rng.integers(-perturbation, perturbation, npi) / 10000.0, rng.uniform(1, Q_LIMIT, npi)))
			edges += [(0, indices[i][0]), (indices[i][-1], n - 1)] + list(zip(indices[i], indices[i][1:]))
		towers.append((0, 0, rng.uniform(1, Q_LIMIT)))
		# print(towers)

		extra_edges = []
		for i in range(num_longitudes):
			j = (i + 1) % num_longitudes
			npi = num_points[i] - 1
			npj = num_points[j] - 1
			cnti = cntj = 0
			lastadd = rng.integers(2)
			while cnti < npi or cntj < npj:
				extra_edges.append((indices[i][cnti], indices[j][cntj]))
				if cnti < npi and cntj < npj:
					if (lastadd == 1) ^ (rng.random() < clumping):
						cnti += 1
					else:
						cntj += 1
				elif cnti == npi:
					cntj += 1
				else:
					cnti += 1
			extra_edges.append((indices[i][cnti], indices[j][cntj]))
		# print(edges, extra_edges)
		
		rng.shuffle(extra_edges)

		edges += extra_edges[:m - len(edges)]

		points = [getPointByParameters(r, tower[0], tower[1]) for tower in towers]
		intersected = False
		for i in range(m):
			for j in range(i + 1, m):
				if len(set([*edges[i], *edges[j]])) == 4 and intersect(points[edges[i][0]], points[edges[i][1]], points[edges[j][0]], points[edges[j][1]]):
					intersected = True
					break
			else:
				continue
			break
		else:
			break


	if use_polars:
		return n, len(edges), l, 0, n - 1, r, rng.uniform(1, K_LIMIT), towers, edges
	else:
		s, t = rng.choice(n, 2, replace = False)
		return n, len(edges), l, s, t, r, rng.uniform(1, K_LIMIT), towers, edges

def genTriangularChrysanthemum(n, m, l = None, rand_st = False, **extra_param):
	side = int((n - 1) ** 0.5)
	assert side % 2 == 0 and side ** 2 + 1 == n
	rng = np.random.default_rng()
	if l is None:
		l = rng.integers(1, L_LIMIT, endpoint = True)
	towers = getPointsNorthContentric(n, **extra_param)
	edges = []
	for j in range(1, side + 1, 2):
		edges += [(0, j), (0, j + 1), (j, j + 1)]
	for i in range(1, side):
		for j in range(1, side + 1, 2):
			x = rng.integers(2)
			edges += [((i - 1) * side + j + x, i * side + j), ((i - 1) * side + j + x, i * side + j + 1), (i* side + j, i * side + j + 1)]
	if rand_st:
		s, t = rng.choice(n, 2, replace = False, shuffle = False)
	else:
		x = rng.integers(side * (side - 1) // 2)
		s = x * 2 + 1
		t = x * 2 + 2
	return n, len(edges), l, s, t, np.round(rng.uniform(10, R_LIMIT), 4), np.round(rng.uniform(1, K_LIMIT), 4), towers, edges

def genQuadrilateralChrysanthemum(n, m, l = None, rand_st = False, **extra_param):
	side = int((n - 1) ** 0.5)
	assert side % 2 == 0 and side ** 2 + 1 == n
	rng = np.random.default_rng()
	if l is None:
		l = rng.integers(1, L_LIMIT, endpoint = True)
	towers = getPointsNorthContentric(n, **extra_param)
	edges = []
	for j in range(1, side + 1, 2):
		edges += [(0, j), (0, j + 1), (j, j + 1)]
	for i in range(1, side):
		for j in range(1, side + 1, 2):
			edges += [((i - 1) * side + j, i * side + j), ((i - 1) * side + j + 1, i * side + j + 1), (i* side + j, i * side + j + 1)]
	if rand_st:
		s, t = rng.choice(n, 2, replace = False, shuffle = False)
	else:
		x = rng.integers(side * (side - 1) // 2)
		s = x * 2 + 1
		t = x * 2 + 2
	return n, len(edges), l, s, t, np.round(rng.uniform(10, R_LIMIT), 4), np.round(rng.uniform(1, K_LIMIT), 4), towers, edges

def getComponents(n, edges):
	vis = np.full(n, -1, dtype = np.int32)
	adj = [[] for i in range(n)]
	for e in edges:
		adj[e[0]].append(e[1])
		adj[e[1]].append(e[0])
	components = []
	for i in range(n):
		if vis[i] == -1:
			vis[i] = i
			q = [i]
			j = 0
			while j < len(q):
				for v in adj[q[j]]:
					if vis[v] == -1:
						q.append(v)
						vis[v] = i
				j += 1
			components.append(q)
	return components

class DSU:
	def __init__(self, n, edges):
		self.fa = [i for i in range(n)]
		self.num_components = n
		for edge in edges:
			self.connect(*edge)
	
	def get_num_components(self):
		return self.num_components
	
	def find(self, node):
		if self.fa[node] != node:
			self.fa[node] = self.find(self.fa[node])
		return self.fa[node]
	
	def connect(self, u, v):
		u = self.find(u)
		v = self.find(v)
		if u != v:
			self.num_components -= 1
			self.fa[u] = v
	
	def is_connected(self, u, v):
		return self.find(u) == self.find(v)

def addRandomEdges(n, m, points, edges = None, permanent_edges = None, unused_edges = None, remove_old = 0.5, quick_return = 0.1, allow_extra_edges = False, **extra_param):
	rng = np.random.default_rng()
	if edges is None:
		edges = []
	edge_set = set(edges + [(v, u) for u, v in edges])
	if permanent_edges is None:
		permanent_edges = set()
	elif not isinstance(permanent_edges, set):
		permanent_edges = set(permanent_edges + [(v, u) for u, v in permanent_edges])
	if unused_edges is None:
		unused_edges = [(u, v) for u in range(n) for v in range(u + 1, n) if (u, v) not in edge_set]
	dsu = DSU(n, edges)
	
	for try_cnt in range(10):
		print(f"Try {try_cnt}")
		deleted_edges = []
		for i, ue in enumerate(unused_edges):
			count = 0
			for j, fe in enumerate(edges):
				if len(set([*ue, *fe])) == 4 and intersect(points[ue[0]], points[ue[1]], points[fe[0]], points[fe[1]]):
					count += 1
					findex = j
					if count == 2:
						break
			else:
				if count == 0:
					if (dsu.is_connected(*ue) and rng.random() < 0.25) or (len(edges) >= m and not allow_extra_edges):
						deleted_edges.append(ue)
					else:
						edges.append(ue)
						dsu.connect(*ue)
						print(f"{i}/{len(unused_edges)} {len(edges)} {dsu.get_num_components()}")
				else:							# count == 1
					if edges[findex] in permanent_edges:
						continue
					if (rng.random() < remove_old) or (not dsu.is_connected(*ue) and rng.random() < remove_old):
						fe = edges[findex]
						edges[findex] = ue
						new_dsu = DSU(n, edges)
						if new_dsu.get_num_components() > dsu.get_num_components() and rng.random() > 0.1:
							edges[findex] = fe
							deleted_edges.append(ue)
							del new_dsu
						else:
							print(f"Replace {ue} with {fe} since {count = }, #components {dsu.get_num_components()} -> {new_dsu.get_num_components()}.")
							deleted_edges.append(fe)
							dsu = new_dsu
					else:
						deleted_edges.append(ue)
				if len(edges) >= m and dsu.get_num_components() == 1 and (not allow_extra_edges or rng.random() < quick_return):
					deleted_edges = []
					break
		print(f"Progress: {len(edges)}/{m}, {len(deleted_edges)} edges remain.")
		if len(deleted_edges) == 0:
			break
		unused_edges = deleted_edges
	
	components = getComponents(n, edges)
	assert len(components) == 1

	return edges

def genSTBridge(n, m, l = None, **extra_param):
	rng = np.random.default_rng()
	if l is None:
		l = rng.integers(1, L_LIMIT, endpoint = True)
	a = rng.integers(10000, size = n, endpoint = True)
	b = rng.integers(20000, size = n)
	assert len(set([(a[i], b[i]) for i in range(n)])) == n
	s = np.argmax(np.where(a <= 5000, a, 0))
	t = np.argmin(np.where(a > 5000, a, 10000))
	r = np.round(rng.uniform(10, R_LIMIT), 4)
	points = [getPointByParameters(r, a[i] / 10000.0, b[i] / 10000.0) for i in range(n)]
	towers = list(zip(a / 10000.0, b / 10000.0, rng.uniform(1, Q_LIMIT, n).round(4)))
	edges = [(s, t)]
	edge_set = {(s, t), (t, s)}
	types = np.full(n, -1, dtype = np.int32)
	types[s] = 0
	types[t] = 1
	for i in range(n):
		if i != s and i != t:
			if a[i] <= 5000:
				edges.append((i, s))
				edge_set.update([(i, s), (s, i)])
				types[i] = 0
			else:
				edges.append((i, t))
				edge_set.update([(i, t), (t, i)])
				types[i] = 1
	unused_edges = [(i, j) for i in range(n) for j in range(i + 1, n) if types[i] == types[j] and (i, j) not in edge_set]
	edges = addRandomEdges(n, m, points, edges, edge_set, unused_edges, **extra_param)
	
	return n, len(edges), l, s, t, r, np.round(rng.uniform(1, K_LIMIT), 4), towers, edges

def genUniform(n, m, l = None, num_warm_edges = 0, choose_adjacent_st = False, **extra_param):
	rng = np.random.default_rng()
	if l is None:
		l = rng.integers(1, L_LIMIT, endpoint = True)
	a = rng.integers(10000, size = n, endpoint = True)
	b = rng.integers(20000, size = n)
	assert len(set([(a[i], b[i]) for i in range(n)])) == n
	r = np.round(rng.uniform(10, R_LIMIT), 4)
	points = [getPointByParameters(r, a[i] / 10000.0, b[i] / 10000.0) for i in range(n)]
	towers = list(zip(a / 10000.0, b / 10000.0, rng.uniform(1, Q_LIMIT, n).round(4)))
	edges = []
	edge_set = set()
	if num_warm_edges >= n - 1:
		order = rng.permutation(n)
		for i in range(1, n):
			fa = order[rng.integers(i)]
			edges.append((fa, order[i]))
			edge_set.update([(order[i], fa), (fa, order[i])])
		unused_edges = [(i, j) for i in range(n) for j in range(i + 1, n) if (i, j) not in edge_set]
		rng.shuffle(unused_edges)
		edges += unused_edges[: m - n + 1]
		rng.shuffle(edges)
	
		unused_edges = unused_edges[m - n + 1 :]
		final_edges = []
		for i in range(len(edges)):
			for j in range(i + 1, len(edges)):
				if len(set([*edges[i], *edges[j]])) == 4 and intersect(points[edges[i][0]], points[edges[i][1]], points[edges[j][0]], points[edges[j][1]]):
					break
			else:
				# print(f"Add {edges[i]}")
				final_edges.append(edges[i])
		edges = final_edges
	else:
		unused_edges = None
	edges = addRandomEdges(n, m, points, edges, **extra_param)
	if choose_adjacent_st:
		s, t = rng.choice(edges)
	else:
		s, t = rng.choice(n, size = 2, replace = False, shuffle = False)

	return n, len(edges), l, s, t, r, np.round(rng.uniform(1, K_LIMIT), 4), towers, edges

def genTestcase(filename, gen, n, m, **extra_param):
	log(f"Generating input for case {filename}, params: {n = }, {m = }, {gen.__name__}, {extra_param = }")
	# assert ..., "Parameters invalid!"
	n, m, l, s, t, r, k, towers, edges = gen(n, m, **extra_param)
	
	rng = np.random.default_rng()
	node_id = list(range(1, n + 1))
	rng.shuffle(node_id)
	node_id = [0] + node_id
	rev = [0] * (n + 1)
	for i in range(1, n + 1):
		rev[node_id[i]] = i
	rng.shuffle(edges)
	with open(f"{filename}.in", "w") as f:
		print(n, m, l, node_id[s + 1], node_id[t + 1], file = f)
		print(f"{r:.4f} {k:.4f}", file = f)
		for i in range(1, n + 1):
			print("{:.4f} {:.4f} {:.4f}".format(*towers[rev[i] - 1]), file = f)
		for edge in edges:
			x = rng.integers(2)
			print(f"{node_id[edge[x] + 1]} {node_id[edge[1 - x] + 1]}", file = f)
	
	log(f"Generating output for case {filename}")
	# os.system('(time ../ShinyRacers/std < {}.in > {}.ans) 2>> gen.log'.format(filename, filename))
	os.system(f'(time {os.path.join("..", "Wonderseabreeze", "std")} < {filename}.in > {filename}.ans) 2>> gen.log')		# Linux
	# os.system(f'({os.path.join("..", "Wonderseabreeze", "std")} < {filename}.in > {filename}.ans) 2>> gen.log')				# Windows

class Cases:
	def __init__(self, prefix = ""):
		self.cnt = 0
		self.prefix = prefix
	
	def gen(self, gen, n, m, **extra_param):
		self.cnt += 1
		genTestcase(f"{self.prefix}{self.cnt}", gen, n, m, **extra_param)
	
	def skip(self, cnt = 1):
		self.cnt += cnt

# os.system("rm gen.log")
testcase = Cases()
# precase = Cases("../pre/")
sample = Cases("../down/")

sample.skip(1)
sample.gen(genUniform, 14, 36)

for i in range(1, TASK_NUM + 1):
	log("Generating subtask {}".format(i))
	pre = testcase.cnt
	# pre_pre = precase.cnt
	# add testcases below
	rng = np.random.default_rng()

	'''
	testcase.gen(genChain, N_LIMIT, 499)
	for gen in (genTriangularChrysanthemum, genQuadrilateralChrysanthemum):
		for rand_st in (True, False):
			testcase.gen(gen, 485, None, rand_st = rand_st)
	testcase.gen(genSTBridge, N_LIMIT, 1200)
	'''
	testcase.skip(6)

	for m in (1200, 1400):
		for num_warm_edges in (0, 1000):
			testcase.gen(genUniform, N_LIMIT, m, num_warm_edges = num_warm_edges, choose_adjacent_st = True)
			testcase.gen(genUniform, N_LIMIT, m, num_warm_edges = num_warm_edges, choose_adjacent_st = False)
	for cnt in range(5):
		n = rng.integers(20, 40)
		testcase.gen(genUniform, n, 2 * n, choose_adjacent_st = [True, False][rng.integers(2)], allow_extra_edges = True)

	for m in (1200, 1400, 3 * N_LIMIT - 6):
		for num_longitudes in (20, 30, 40, 50):
			testcase.gen(genGrid, N_LIMIT, m, num_longitudes = num_longitudes)
	testcase.gen(genGrid, N_LIMIT, 1400, num_longitudes = 30, use_polars = False)
	testcase.gen(genGrid, N_LIMIT, 1400, num_longitudes = 30, clumping = 0.8)
	
	'''
	for cnt in range(9):
		testcase.gen(genGrid, 31 * 32 + 2, 0, use_polars = [True, False][random.randint(0, 1)])
	'''
	
	# add testcases above		
	log("Subtask {} done. ({} - {})".format(i, pre + 1, testcase.cnt))
	# log("Subtask {} done. (test: {} - {}; pre: {} - {})".format(i, pre + 1, testcase.cnt, pre_pre + 1, precase.cnt))

# for duck
# os.system("mkdir download")
# os.system("cp ../down/* ./download/")
