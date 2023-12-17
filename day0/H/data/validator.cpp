#include"testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
	registerValidation(argc, argv);
	int n = inf.readInt(1, 1000000, "n"); inf.eoln();
	string s = inf.readString("[0-9]*", "s"); inf.readEof();
	quitif((int)s.length() != n, _fail, "Length of s should be %d\n", n);
	for (int i = 0; i < n; i++) quitif(s[i] != '0' && s[i] != '1', _fail, "s[%d] should be 0 or 1.\n", i);
	return 0;
}