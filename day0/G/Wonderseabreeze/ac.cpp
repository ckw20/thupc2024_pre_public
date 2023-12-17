#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define cmax(_a, _b) (_a < (_b) ? _a = (_b) : 0)
#define dmin(_a, _b) ((_a) < (_b) ? (_a) : (_b))
#define dmax(_a, _b) ((_a) > (_b) ? (_a) : (_b))
typedef vector<int> vi;
struct Edge{
	int to, next;
} e[306];
int head[306], siz[306], marken[306], fa[306], lch[306], rch[306], ch[306][2], side[306], outps[306];
int r[306], p[306], op[603], nhuman[603], start[306], vis[603][45459][2], n, q, tot;
long long sump[306][306], outsum[306][306], f[603][45459][2];
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
long long dp(int step, int o, int lcnt, int rcnt, int moved){
	if (lcnt > siz[ch[o][0]] || rcnt > siz[ch[o][1]]) return -1;
	int outcnt = nhuman[step - 1] - lcnt - rcnt;
	if (outcnt < 0 || outcnt > n - siz[o]) return -2;
	if (step > q) return 0;
	int state;
	if (vis[step][state = start[o] + lcnt * (siz[ch[o][1]] + 1) + rcnt][moved]) return f[step][state][moved];
	// fprintf(stderr, "@(%d, %d, %d, %d, %d) (out = %d)\n", step, o, lcnt, rcnt, moved, outcnt);
	long long now = -1, tmp;
	vis[step][state][moved] = 1;
	switch (op[step]) {
		case 1:
			if (moved) {
				tmp = dp(step + 1, o, lcnt, rcnt, 0);
				if (tmp >= 0) now = tmp + sump[ch[o][0]][lcnt] + sump[ch[o][1]][rcnt] + r[o] + outsum[o][outcnt];
			}
			if (o != 1) {
				int fao = fa[o], sumcnt = lcnt + rcnt;
				// fprintf(stderr, "\tto fa(%d, side%d): [0, %d]\n", fao, side[o], dmin(outcnt, siz[ch[fao][side[o] ^ 1]]));
				if (side[o]) {
					for (int i = dmin(outcnt, siz[ch[fao][0]]); i >= 0; --i) {
						tmp = dp(step, fao, i, sumcnt, 1);
						if (tmp == -2) break;
						cmax(now, tmp);
					}
				}
				else {
					for (int i = dmin(outcnt, siz[ch[fao][1]]); i >= 0; --i) {
						tmp = dp(step, fao, sumcnt, i, 1);
						if (tmp == -2) break;
						cmax(now, tmp);
					}
				}
			}
			break;
		case 2:
			if (moved) {
				tmp = dp(step + 1, o, lcnt, rcnt, 0);
				if (tmp >= 0) now = tmp + sump[ch[o][0]][lcnt] + sump[ch[o][1]][rcnt] + r[o] + outsum[o][outcnt];
			}
			if (ch[o][0]) {
				// Left
				int c, lim;
				if ((c = ch[o][0]) && lcnt < siz[ch[o][0]]) {
					lim = dmin(siz[ch[c][1]], lcnt);
					// fprintf(stderr, "\tto left(%d): [%d, %d]\n", c, dmax(lcnt - siz[ch[c][0]], 0), lim);
					for (int i = dmax(lcnt - siz[ch[c][0]], 0); i <= lim; ++i) {
						tmp = dp(step, c, lcnt - i, i, 1);
						cmax(now, tmp);
					}
				}
				// Right
				if ((c = ch[o][1]) && rcnt < siz[ch[o][1]]) {
					lim = dmin(siz[ch[c][1]], rcnt);
					// fprintf(stderr, "\tto right(%d): [%d, %d]\n", c, dmax(rcnt - siz[ch[c][0]], 0), lim);
					for (int i = dmax(rcnt - siz[ch[c][0]], 0); i <= lim; ++i) {
						tmp = dp(step, c, rcnt - i, i, 1);
						cmax(now, tmp);
					}
				}
			}
			break;
		case 3:
			if (outcnt + 1 <= n - siz[o]) {
				tmp = dp(step + 1, o, lcnt, rcnt, 0);
				if (tmp >= 0) now = tmp + sump[ch[o][0]][lcnt] + sump[ch[o][1]][rcnt] + r[o] + outsum[o][outcnt + 1];
			}
			break;
		case 4:
			if (outcnt >= 1) {
				tmp = dp(step + 1, o, lcnt, rcnt, 0);
				if (tmp >= 0) now = tmp + sump[ch[o][0]][lcnt] + sump[ch[o][1]][rcnt] + r[o] + outsum[o][outcnt - 1];
			}
			break;
	}
	// fprintf(stderr, "?(%d, %d, %d, %d, %d) = %lld\n", step, o, lcnt, rcnt, moved, now);
	return f[step][state][moved] = now;
}
int main(){
	int i, j, s, outtot;
	long long ans;
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
	
	ans = dp(1, s, 0, 0, 0);
	if (ans == -1) puts("No solution.");
	else printf("%lld\n", ans);
	return 0;
}