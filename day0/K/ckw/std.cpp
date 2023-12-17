#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
using namespace std;
const int n = 5;
int ft[10][10] = {
	{1, 1, 0},
	{2, 2, 2, 1},
	{3, 2, 2, 3, 0},
	{3, 3, 3, 3, 0},
	{4, 2, 2, 3, 3, 0},
	{4, 2, 3, 3, 4, 1},
	{4, 3, 3, 4, 4, 1},
	{4, 4, 4, 4, 4, 0}
};

char s[n][n + 10];
int b[n][n], _ft[10];
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
	int T; scanf("%d", &T);
	while (T--) {
		rep (i, 0, n - 1) scanf("%s", s[i]);
		rep (i, 0, n - 1) rep (j, 0, n - 1) b[i][j] = (s[i][j] == 'o');
		int cnt = gen_feature(b, n, n, _ft), has_ans = 0;
		rep (i, 0, 7) if (ft[i][0] == cnt) {
			int neq = 0;
			rep (j, 1, cnt) neq |= (ft[i][j] != _ft[j]);
			if (!neq) {
				printf(ft[i][cnt + 1]?"Far\n":"Away\n");
				has_ans = 1;
				break;
			}
		}
		assert(has_ans);
	}
	return 0;
}