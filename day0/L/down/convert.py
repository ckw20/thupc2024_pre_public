if __name__ == "__main__":
	commands = []
	
	n, m, l, s, t = map(int, input().split())
	r, k = map(float, input().split())
	r = 1	# Set r = 1 for a better view in default settings; remove this line to visualize real data

	commands.append(f"x^2+y^2+z^2={r}^2")

	points = []
	for i in range(n):
		a, b, q = map(float, input().split())
		points.append(f"(1; {b} pi; {0.5 - float(a):.4f} pi)")
	commands.append(f"towers = {{{', '.join(points)}}}")

	edges = [tuple(input().split()) for i in range(m)]
	us = [edge[0] for edge in edges]
	vs = [edge[1] for edge in edges]
	commands.append(f"ulist = {{{', '.join(us)}}}")
	commands.append(f"vlist = {{{', '.join(vs)}}}")

	commands.append("Zip(CircularArc(O, A, B), A, Zip(towers(i), i, ulist), B, Zip(towers(i), i, vlist))")
	commands.append(f'Sequence(Text("Tower " + (i), towers(i), true), i, 1, {n})')

	print("======= Commands begin =======\n")
	for command in commands:
		print(command + "\n")
	print("======= Commands end =======")