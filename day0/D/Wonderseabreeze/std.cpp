#include <cstdio>
using namespace std;
int f[5004][5004], g[5004][5004];
int lq[5004][5004], rq[5004][5004], ltot[5004], rtot[5004];
char s[5004];
int main(){
	int n, i, j, k, len, ij, lptr, rptr, tmp;
	// int count = 0;
	scanf("%d", &n);
	scanf("%s", s + 1);
	for (i = 1; i <= n; ++i) {
		lptr = i - 1;
		rptr = i + 1;
		for (j = 1; lptr && rptr <= n; ++j, --lptr, ++rptr) {
			if (s[lptr] == s[rptr]) break;
			lq[lptr][++ltot[lptr]] = i;
			rq[rptr][++rtot[rptr]] = i;
		}
	}
	for (i = 1; i <= n; ++i) {
		f[i][i] = 1;
		lq[i][ltot[i] + 1] = rq[i][rtot[i] + 1] = n + 1;
	}
	for (len = 2; len <= n; ++len) {
		for (i = 1, j = len; j <= n; ++i, ++j) {
			if (f[i + 1][j] < f[i][j - 1] || (f[i + 1][j] == f[i][j - 1] && g[i + 1][j] < g[i][j - 1])) {
				f[i][j] = f[i + 1][j] + 1;
				g[i][j] = g[i + 1][j] + len - 1;
			}
			else {
				f[i][j] = f[i][j - 1] + 1;
				g[i][j] = g[i][j - 1] + len - 1;
			}
			for (rptr = rtot[j]; rq[j][rptr] > i; --rptr);
			++rptr;
			ij = i + j;
			for (lptr = 1; lq[i][lptr] < j || rptr <= rtot[j]; ) {
				if (lq[i][lptr] <= rq[j][rptr]) {
					k = lq[i][lptr];
					++lptr;
					if (rq[j][rptr] == k) ++rptr;
				}
				else {
					k = rq[j][rptr];
					++rptr;
				}
				// ++count;
				if (k * 2 >= ij) {
					if (f[i][k - 1] + 1 < f[i][j]) {
						f[i][j] = f[i][k - 1] + 1;
						g[i][j] = g[i][k - 1] + k * 2 - ij;
					}
					else if (f[i][k - 1] + 1 == f[i][j] && (tmp = g[i][k - 1] + k * 2 - ij) < g[i][j]) {
						g[i][j] = tmp;
					}
				}
				else {
					if (f[k + 1][j] + 1 < f[i][j]) {
						f[i][j] = f[k + 1][j] + 1;
						g[i][j] = g[k + 1][j] + ij - k * 2;
					}
					else if (f[k + 1][j] + 1 == f[i][j] && (tmp = g[k + 1][j] + ij - k * 2) < g[i][j]) {
						g[i][j] = tmp;
					}
				}
			}
		}
	}
	
	printf("%d %d\n", f[1][n], g[1][n]);
	// fprintf(stderr, "%d\n", count);
	return 0;
}