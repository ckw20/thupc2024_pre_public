#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a);i <= (b); i++)
#define Rep(i, v) rep(i, 0, (int)v.size() - 1)
#define lint long long
#define ull unsigned lint
#define db long double
#define pb push_back
#define mp make_pair
#define fir first
#define sec second
#define debug(x) cerr << #x << " = " << x
#define sp << " "
#define ln << endl
using namespace std;
typedef pair<int, int> pii;
typedef set<int>::iterator sit;
const int N = 1000010;
char s[N]; int a[N];
vector<int> ps;
inline int getl(int p, int len, int v) {
	if (!a[p]) return 0;
	int q = p, u = a[q];
	while (q <= len && u <= v) {
		if (u == v) return q - p + 1;
		u = (u << 1) + a[++q];
	}
	return 0;
}
int main() {
	int n; scanf("%d%s", &n, s + 1);
	rep (i, 1, n) a[i] = s[i] ^ '0';
	int len = n;
	rep (v, 1, n) {
		ps.clear();
		rep (i, 1, len) {
			int l = getl(i, len, v);
			if (l != 0) ps.pb(i);
		}
		if (ps.size()) {
			printf("%d %d\n", ps[0], (int)ps.size());
			int p = ps[0], l = getl(p, len, v);
			rep (j, p, len - l) a[j] = a[j + l];
			len -= l;
		}
		else printf("-1 0\n");
	}
}