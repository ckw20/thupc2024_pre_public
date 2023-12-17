#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
#define lint long long
using namespace std;
const int n = 5;
int a[n][n], b[n][n], w, h;
unordered_map<lint, int> fws;
#define P(i, j) ((i) * n + (j))
inline bool chk_con() {
	rep (i, 0, n - w) rep (j, 0, n - h) {
		bool neq = 0;
		rep (k, 0, w - 1) rep (t, 0, h - 1) neq |= (a[i + k][j + t] != b[k][t]);
		if (!neq) return true;
	}
	return false;
}
inline int fir_win(int cnt, int id) {
	if (fws.count(id)) return fws[id]; int fw = 0;
	if (chk_con()) fw = (cnt % 3 != 0);
	else {
		rep (i, 0, n - 1) rep (j, 0, n - 1) if (!a[i][j])
			a[i][j] = 1, fw |= !fir_win(cnt + 1, id ^ (1 << P(i, j))), a[i][j] = 0;
	}

	// rep (i, 0, n - 1) { rep (j, 0, n - 1) cerr << a[i][j]; cerr << endl; }
	// debug(cnt)sp, debug(id)sp, debug(fw)ln ln;
	return fws[id] = fw;
}

int ft[10];
inline int gen_feature(int b[n][n], int w, int h, int *ft) {
	int &cnt = ft[0] = 0;
	rep (i, 0, w - 1) rep (j, 0, h - 1) if (b[i][j]) {
		ft[++cnt] = 0;
		rep (k, -1, 1) rep (t, -1, 1) {
			int x = i + k, y = j + t;
			if (x < 0 || x >= w || y < 0 || y >= h) continue;
			ft[cnt] += b[x][y];
		}
	}
	sort(ft + 1, ft + cnt + 1);
	return cnt;
}
int main() {
	printf("int ft[10][10] = {\n");
	while (scanf("%d%d", &w, &h) != EOF) {
		rep (i, 0, w - 1) rep (j, 0, h - 1) scanf("%1d", &b[i][j]);
		fws.clear(); rep (i, 0, n - 1) rep (j, 0, n - 1) a[i][j] = 0;
		int fw = fir_win(0, 0), cnt = gen_feature(b, w, h, ft);

		static int las = 0; if (las) printf(",\n"); las = 1;
		printf("\t{%d", cnt);
		rep (i, 1, cnt) printf(", %d", ft[i]);
		printf(", %d}", fw);
	}
	printf("\n};\n");
	return 0;
}