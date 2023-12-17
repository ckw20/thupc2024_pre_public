#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a);i <= (b); i++)
using namespace std; const int N = 1000010;

namespace OUTPUT_SPACE{
	char s[1000000 * 30], t[20]; int n, m;
	inline void Flush() { fwrite(s + 1, sizeof(char), n, stdout), n = 0; }
	inline void print(int x) {
		if(!x) s[++n] = '0';
		for(m = 0; x; x /= 10) t[++m] = char(x % 10 + '0');
		for(; m; m--) s[++n] = t[m];
	}
	inline void PC(char ch) { s[++n] = ch; }
}using OUTPUT_SPACE::print; using OUTPUT_SPACE::PC; using OUTPUT_SPACE::Flush;

template<typename _Tp, typename _Sequence = vector<_Tp>,
		typename _Compare  = less<typename _Sequence::value_type> >
struct myset {
	priority_queue<_Tp, _Sequence, _Compare> h, d;
	_Tp result;
	inline void insert(_Tp x) { h.push(x); }
	inline void erase(_Tp x) { d.push(x); }
	inline size_t size() { return h.size() - d.size(); }
	inline bool empty() { return h.size() == d.size(); }
	inline _Tp *begin() {
		while (!d.empty() && h.top() == d.top()) h.pop(), d.pop();
		return &(result = h.top());
	}
};
myset<int, vector<int>, greater<int> > ps[N];
char s[N]; int n, curv, a[N], L[N], R[N], b[N];

#define lb(x) ((x) & (-(x)))
inline void update(int p, int v = 1) { while (p <= n) b[p] += v, p += lb(p); }
inline int query(int p, int ans = 0) { while (p) ans += b[p], p ^= lb(p); return ans; }
inline void update_ps(int p, int l, int v, int d) {
	if (!a[l]) return ;
	for (int q = p; q <= n && (v = (v << 1) + a[q]) <= n; q = R[q])
		if (v > curv) { if (d) ps[v].erase(l); else ps[v].insert(l); }
}

int main() {
	scanf("%d", &n), fread(s, 1, n + 1, stdin);
	rep (i, 1, n) a[i] = s[i] ^ '0';
	rep (i, 1, n + 1) L[i] = i - 1, R[i - 1] = i;
	rep (i, 1, n) update_ps(i, i, 0, 0);
	rep (v, 1, n)
		if (ps[curv = v].empty()) PC('-'), PC('1'), PC(' '), PC('0'), PC('\n');
		else {
			int p = *ps[v].begin(), l = L[p], r = p;
			print(p - query(p)), PC(' '), print((int)ps[v].size()), PC('\n');
			for (int u = 0; u < v; u = (u << 1) + a[r], r = R[r]) update(r, 1), update_ps(r, r, 0, 1);
			for (int u = 0, t = 0; l > 0 && (1 << t) <= n && (u += a[l] << t) <= n; l = L[l], t++) update_ps(p, l, u, 1), update_ps(r, l, u, 0);
			L[r] = L[p], R[L[p]] = r;
		}
	return Flush(), 0;
}