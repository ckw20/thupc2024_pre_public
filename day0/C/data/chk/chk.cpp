#include"testlib.h"
#include <bits/stdc++.h>
#define re register
using namespace std;

int main(int argc, char* argv[]) {
	// Also the validator
	registerLemonChecker(argc, argv);
	int n = inf.readInt(1, 1000000000, "n");
	double p = inf.readStrictDouble(0.000001, 0.999999, 1, 6, "p");
	int l = inf.readInt(1, n, "l"), r = inf.readInt(l, n, "r");
	double expected = ans.readDouble(), result = ouf.readDouble();
	if(!doubleCompare(expected, result, 1e-6)) quitf(_wa, "Wrong Answer");
	quitf(_ok, "Accepted");
	return 0;
}