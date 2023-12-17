#include <cstdio>
using namespace std;
#define HIGH_DIGIT 0x1'0000'0000ll
#define INF 0x4000'0000'0000ll
#define cmin(_a, _b) (_a > (_b) ? _a = (_b) : 0)
#define dmin(_a, _b) ((_a) < (_b) ? (_a) : (_b))
long long f[5004][5004];
int lq[5004][5004], rq[5004][5004], ltot[5004], rtot[5004];
char s[5004];
int main(){
	int n, i, j, k, len, ij, lptr, rptr, mid;
	long long now, tmp;
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
		f[i][i] = HIGH_DIGIT;
		lq[i][ltot[i] + 1] = rq[i][rtot[i] + 1] = n + 1;
	}
	for (i = n - 1; i; --i) {
		for (j = i + 1; j <= n; ++j) {
			now = dmin(f[i + 1][j], f[i][j - 1]) + j - i;
			ij = i + j;
			mid = ij >> 1;
			for (rptr = rtot[j]; (k = rq[j][rptr]) > mid; --rptr) {
				tmp = f[i][k - 1] + k * 2 - ij;
				cmin(now, tmp);
			}
			for (lptr = 1; (k = lq[i][lptr]) <= mid; ++lptr) {
				tmp = f[k + 1][j] + ij - k * 2;
				cmin(now, tmp);
			}
			f[i][j] = now + HIGH_DIGIT;
		}
	}
	
	printf("%lld %lld\n", f[1][n] >> 32, f[1][n] & (HIGH_DIGIT - 1));
	// fprintf(stderr, "%d\n", count);
	return 0;
}