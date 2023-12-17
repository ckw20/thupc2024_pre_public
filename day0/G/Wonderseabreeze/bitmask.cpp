#include <cstdio>
#include <cstring>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;
#define INF 0x3f3f3f3f'3f3f3f3fll
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
#define dmin(_a, _b) ((_a) < (_b) ? (_a) : (_b))
#define dmax(_a, _b) ((_a) > (_b) ? (_a) : (_b))
typedef vector<int> vi;
struct Edge{
	int to, next;
} e[306];
int head[306], siz[306], marken[306], fa[306], lch[306], rch[306], ch[306][2], side[306], outps[306];
int r[306], p[306], op[603], nhuman[603], start[306], n, q, tot;
long long sump[306][306], outsum[306][306], f[54][2][18][33003];
int cnt[33003];
long long profit[18][33003];
vi merge(const vi& a, const vi& b) {
	vi ret;
	auto ita = a.cbegin(), itb = b.cbegin();
	while (ita != a.cend() && itb != b.cend()) {
		if (*ita > *itb) ret.push_back(*(ita++));
		else ret.push_back(*(itb++));
	}
	if (ita != a.cend()) {
		do ret.push_back(*(ita++)); while (ita != a.cend());
	}
	else {
		do ret.push_back(*(itb++)); while (itb != b.cend());
	}
	return ret;
}
vi dfs(int o) {
	siz[o] = 1;
	if (head[o] == 0) {
		sump[o][1] = p[o];
		start[o] = tot;
		++tot;
		return (vi){p[o]};
	}
	int i, to;
	vi ps{p[o]};
	for (i = head[o]; i; i = e[i].next) {
		vi psto = dfs(to = e[i].to);
		siz[o] += siz[to];
		ps = merge(ps, psto);
		if (ch[o][0]) side[ch[o][1] = to] = 1;
		else ch[o][0] = to;
	}
	for (i = 0; i < ps.size(); ++i) {
		sump[o][i + 1] = sump[o][i] + ps[i];
	}
	start[o] = tot;
	tot += (siz[ch[o][0]] + 1) * (siz[ch[o][1]] + 1);
	return ps;
}
void mark(int o) {
	marken[o] = 1;
	for (int i = head[o]; i; i = e[i].next) {
		mark(e[i].to);
	}
	return ;
}
int count(int x, int manned, int o) {
	int now = marken[o];
	for (int i = head[o]; i; i = e[i].next) {
		now += count(x, manned, e[i].to);
	}
	if (o == ch[x][0] || o == ch[x][1]) profit[x][manned] += sump[o][now];
	else if (o == x) return 0;
	return now;
}

struct State {
	long long val;
	int node, state;
	inline bool operator < (const State &x) const {
		return val == x.val \
			? (node == x.node ? state > x.state : node > x.node) \
			: val > x.val;
	}
};
deque<State> q0, q1;
int main(){
	int i, j, l, s, u, v, outtot, S, T, U, qptr, pptr;
	long long ans = -1;
	State now;
	scanf("%d %d %d", &n, &q, &s);
	for (i = 2; i <= n; ++i) {
		scanf("%d", &fa[i]);
		e[i] = (Edge){i, head[fa[i]]};
		head[fa[i]] = i;
	}
	for (i = 2; i <= n; ++i) scanf("%d", &r[i]);
	for (i = 2; i <= n; ++i) scanf("%d", &p[i]);
	dfs(1);
	for (i = 1; i <= q; ++i) {
		scanf("%d", &op[i]);
		switch (op[i]) {
			case 3: nhuman[i] = nhuman[i - 1] + 1; break;
			case 4: nhuman[i] = nhuman[i - 1] - 1; break;
			default: nhuman[i] = nhuman[i - 1];
		}
	}
	
	for (i = 2; i <= n; ++i) {
		memset(marken, 0, sizeof(marken));
		mark(i);
		outtot = 0;
		for (j = 1; j <= n; ++j) {
			if (marken[j] == 0) outps[++outtot] = p[j];
		}
		sort(outps + 1, outps + outtot + 1);
		for (j = 0; j < outtot; ++j) outsum[i][j + 1] = outsum[i][j] + outps[outtot - j];
	}
	
	U = (1 << n) - 1;
	for (S = 1; S <= U; ++S) cnt[S] = cnt[S ^ (S & -S)] + 1;
	for (i = 1; i <= n; ++i) {
		U = ((1 << n) - 1) ^ (1 << (i - 1));
		for (S = U; S >= 0; --S) {
			S &= U;
			for (j = 1; j <= n; ++j) {
				marken[j] = (S >> j - 1) & 1;
			}
			outtot = count(i, S, 1);
			profit[i][S] += r[i] + outsum[i][outtot];
		}
	}
	
	// for convenience
	for (i = 2; i <= n; ++i) {
		e[i + n] = (Edge){fa[i], head[i]};
		head[i] = i + n;
	}
	
	memset(f, -1, sizeof(f));
	f[1][0][s][0] = 0;
	q0.push_back((State){0, s, 0});
	for (i = 1; i <= q && !q0.empty(); ++i) {
		for (auto &item : q0) item.val = f[i][0][item.node][item.state];
		sort(q0.begin(), q0.end());
		q1.clear();
		while (!q0.empty()) {
			now = q0.front();
			q0.pop_front();
			if (f[i][0][j = now.node][S = now.state] == INF) continue;
			// fprintf(stderr, "(%d, 0, %d, %d) = %lld\n", i, j, S, f[i][0][j][S]);
			for (u = 1; u <= n; ++u) {
				if (S & (1 << u - 1)) {
					for (l = head[u]; l; l = e[l].next) {
						if ((v = e[l].to) != j && (S & 1 << v - 1) == 0) {
							T = S ^ (1 << v - 1) ^ (1 << u - 1);
							if (f[i][0][j][T] < f[i][0][j][S]) {
								q0.push_front((State){f[i][0][j][T] = f[i][0][j][S], j, T});
							}
						}
					}
				}
			}
			switch (op[i]) {
				case 1:
					if ((v = fa[j]) && (S & 1 << v - 1) == 0 && f[i][1][v][S] < f[i][0][j][S]) {
						q1.push_back((State){f[i][1][v][S] = f[i][0][j][S], v, S});
					}
					break;
				case 2:
					for (l = head[j]; l; l = e[l].next) {
						if ((v = e[l].to) != fa[j] && (S & 1 << v - 1) == 0) {
							q1.push_back((State){f[i][1][v][S] = f[i][0][j][S], v, S});
						}
					}
					break;
				case 3:
					if (j != 1 && (S & 1) == 0) {
						q1.push_back((State){f[i][1][j][S ^ 1] = f[i][0][j][S], j, S ^ 1});
					}
					break;
				case 4:
					if (j != 1 && (S & 1)) {
						q1.push_back((State){f[i][1][j][S ^ 1] = f[i][0][j][S], j, S ^ 1});
					}
					break;
			}
			f[i][0][j][S] = INF;
		}
		
		q0.clear();
		while (!q1.empty()) {
			now = q1.front();
			q1.pop_front();
			if (f[i][1][j = now.node][S = now.state] == INF) continue;
			// fprintf(stderr, "(%d, 1, %d, %d) = %lld <%lld>\n", i, j, S, now.val, f[i][1][j][S]);
			q0.push_back((State){f[i + 1][0][j][S] = now.val + profit[j][S], j, S});
			switch (op[i]) {
				case 1:
					// fprintf(stderr, "\t%d %d\n", fa[j], f[i][1][fa[j]][S]);
					if ((v = fa[j]) && (S & 1 << v - 1) == 0 && f[i][1][v][S] < f[i][1][j][S]) {
						q1.push_front((State){f[i][1][v][S] = f[i][1][j][S], v, S});
					}
					break;
				case 2:
					for (l = head[j]; l; l = e[l].next) {
						if ((v = e[l].to) != fa[j] && (S & 1 << v - 1) == 0 && f[i][1][v][S] < f[i][1][j][S]) {
							q1.push_front((State){f[i][1][v][S] = f[i][1][j][S], v, S});
						}
					}
					break;
			}
			f[i][1][j][S] = INF;
		}
	}
	
	for (auto item : q0) {
		cmax(ans, f[q + 1][0][item.node][item.state]);
	}
	
	if (ans == -1) puts("No solution.");
	else printf("%lld\n", ans);
	return 0;
}