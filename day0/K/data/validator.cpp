#include"testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int n = 5;
int a[n + 5][n + 5], vis[n + 5][n + 5];
inline void dfs(int x, int y) {
	if (x < 1 || x > n || y < 1 || y > n || !a[x][y] || vis[x][y]) return;
	vis[x][y] = 1, dfs(x - 1, y), dfs(x + 1, y), dfs(x, y - 1), dfs(x, y + 1);
}
int main(int argc, char* argv[]) {
	registerValidation(argc, argv);
	int T = inf.readInt(1, 200, "T"); inf.eoln();
	while (T--) {
		for (int i = 1; i <= n; i++) {
			string s = inf.readString(); inf.eoln();
			quitif((int)s.length() != n, _fail, "Length of s should be %d\n", n);
			for (int j = 0; j < n; j++) quitif(s[j] != 'o' && s[j] != '.', _fail, "s[%d] should be '.' or 'o'.\n", j);
			for (int j = 0; j < n; j++) a[i][j + 1] = (s[j] == 'o');
		}
		int cnt = 0;
		for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) vis[i][j] = 0;
		for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++)
			if (a[i][j]) { dfs(i, j); break; }
		for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++)
			if (a[i][j]) cnt++, quitif(!vis[i][j], _fail, "Not connected.\n");
		quitif(cnt == 0, _fail, "Must have at least 1 'o'.\n");
		quitif(cnt > 4, _fail, "Must have no more than 4 'o'.\n");
	}
	inf.readEof();
	return 0;
}