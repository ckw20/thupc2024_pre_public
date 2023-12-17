#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define cmin(_a, _b) (_a > (_b) ? _a = (_b) : 0)
const long double pi = acosl(-1);
typedef vector<int> vecint; 
struct Point {
	long double x, y, z;
	Point() {
		x = y = z = 0;
	}
	Point(long double R, long double theta, long double phi) {
		x = R * sinl(theta) * cosl(phi);
		y = R * sinl(theta) * sinl(phi);
		z = R * cosl(theta);
	}
	inline long double operator * (const Point &p) const {
		return x * p.x + y * p.y + z * p.z;
	}
} p[504], tmp;
struct Matrix {
	long double a[3][3];
	Matrix() {
		memset(a, 0, sizeof(a));
	}
	Matrix operator * (const Matrix &m) const {
		int i, j;
		Matrix ret;
		for (i = 0; i < 3; ++i) {
			for (j = 0; j < 3; ++j) {
				ret.a[i][0] += a[i][j] * m.a[j][0];
				ret.a[i][1] += a[i][j] * m.a[j][1];
				ret.a[i][2] += a[i][j] * m.a[j][2];
			}
		}
		return ret;
	}
	Point operator * (const Point &p) const {
		Point ret;
		ret.x = a[0][0] * p.x + a[0][1] * p.y + a[0][2] * p.z;
		ret.y = a[1][0] * p.x + a[1][1] * p.y + a[1][2] * p.z;
		ret.z = a[2][0] * p.x + a[2][1] * p.y + a[2][2] * p.z;
		return ret;
	}
} rt[504];
Matrix rotate_y(long double theta) {
	Matrix ret;
	ret.a[0][0] = ret.a[2][2] = cosl(theta);
	ret.a[2][0] = -(ret.a[0][2] = sinl(theta));
	ret.a[1][1] = 1;
	return ret;
}
Matrix rotate_z(long double theta) {
	Matrix ret;
	ret.a[0][0] = ret.a[1][1] = cosl(theta);
	ret.a[0][1] = -(ret.a[1][0] = sinl(theta));
	ret.a[2][2] = 1;
	return ret;
}
Matrix rotate_to_north(long double theta, long double phi){
	return rotate_y(-theta) * rotate_z(-phi);
}
struct State {
	long double val;
	int node;
	int destr;
	int cross;
};
struct Edge {
	long double w;
	int to;
	int next;
} ep[3006], ed[3006];
long double theta[504], phi[504], q[504], rot_theta[504], dis[1503][9][2], cap[1503];
int headp[504], headd[1008], suc[3006], elist[1008], fid[3006], epn = 1, edn = 1;
int vis[504], marked[1503][9][2], que[504], pre[504], pledge[504], eonslit[3006], vonslit[504], sstart[504], send[504], ecross[3006], crossfv[1008][504];
vecint vlist[1008];
bool cmp(const int &i, const int &j){
	return rot_theta[ep[i].to] < rot_theta[ep[j].to];
}
bool heapcmp(const State &i, const State &j){
	return i.val == j.val \
		? (i.destr == j.destr ? (\
			i.node == j.node ? i.cross > j.cross : i.node > j.node
		) : i.destr > j.destr) \
		: i.val > j.val;
}
struct Heap {
	State h[81018];		// 3 * M * (L + 1) * 2
	State pq[81018];
	int tot, qh, qt;
	Heap() {
		tot = qh = 0;
		qt = -1;
	}
	void push_front(const State &s) {
		pq[++qt] = s;
		return ;
	}
	void insert(const State &s) {
		h[++tot] = s;
		push_heap(h + 1, h + tot + 1, heapcmp);
		return ;
	}
	void pop() {
		if (qh <= qt) {
			++qh;
			if (qh > qt) qh = 0, qt = -1;
		}
		else {
			pop_heap(h + 1, h + tot + 1, heapcmp);
			--tot;
		}
		return ;
	}
	State top() const {
		if (qh <= qt) return pq[qh];
		return h[1];
	}
	bool empty() const {
		return tot == 0 && qh > qt;
	}
	void clear() {
		tot = qh = 0;
		qt = -1;
		return ;
	}
} h;
int main(){
	int n, m, l, s, t, i, j, u, v, du, cu, dv, cv, fn, cnt, qh, qt;
	long double r, k, ans = 1e200, arclen;
	State now;
	scanf("%d %d %d %d %d", &n, &m, &l, &s, &t);
	scanf("%Lf %Lf", &r, &k);

	// Read towers
	for (i = 1; i <= n; ++i) {
		scanf("%Lf %Lf %Lf", &theta[i], &phi[i], &q[i]);
		theta[i] *= pi;
		phi[i] *= pi;
		p[i] = Point(r, theta[i], phi[i]);
	}
	// Read primal edges
	for (i = 1; i <= m; ++i) {
		scanf("%d %d", &u, &v);
		arclen = r * acosl(p[u] * p[v] / r / r);
		cap[i] = k * q[u] * q[v] / arclen / arclen;
		// fprintf(stderr, "%d: %Lf\n", i, cap[i]);
		ep[++epn] = (Edge){cap[i], v, headp[u]};
		headp[u] = epn;
		ep[++epn] = (Edge){cap[i], u, headp[v]};
		headp[v] = epn;
	}

	// Determine a s -> t path and slit the sphere along the path
	que[qh = qt = 0] = s;
	while (qh <= qt) {
		u = que[qh++];
		vis[u] = 1;
		for (j = headp[u]; j; j = ep[j].next) {
			if (vis[v = ep[j].to] == 0) {
				que[++qt] = v;
				vis[v] = 1;
				pre[v] = u;
				pledge[v] = j;
				if (v == t) break;
			}
		}
		if (j) break;
	}
	for (u = t; u != s; u = pre[u]) {
		// fprintf(stderr, "> %d <\n", u);
		vonslit[u] = 1;
		eonslit[pledge[u] ^ 1] = eonslit[pledge[u]] = 1;
		ecross[pledge[u]] = 1;
		sstart[pre[u]] = pledge[u];
		send[u] = pledge[u] ^ 1;
	}
	vonslit[t] = 0;
	
	for (i = 1; i <= n; ++i) {
		// fprintf(stderr, "%d:\n", i);
		rt[i] = rotate_to_north(theta[i], phi[i]);
		cnt = 0;
		for (j = headp[i]; j; j = ep[j].next) {
			elist[++cnt] = j;
			v = ep[j].to;
			tmp = rt[i] * p[v];
			rot_theta[v] = atan2l(tmp.y, tmp.x);
		}
		sort(elist + 1, elist + cnt + 1, cmp);
		elist[0] = elist[cnt];
		for (j = 1; j <= cnt; ++j) {
			// fprintf(stderr, "\t%d(->%d, %Lf)%c", elist[j], ep[elist[j]].to, rot_theta[ep[elist[j]].to], " \n"[j == cnt]);
			suc[elist[j] ^ 1] = elist[j - 1];
		}
		if (vonslit[i]) {
			// fprintf(stderr, "<|> %d %d %d %d\n", i, cnt, sstart[i], send[i]);
			memcpy(elist + cnt, elist, cnt * sizeof(int));
			for (j = 0; elist[j] != sstart[i]; ++j);
			for (++j; elist[j] != send[i]; ++j) ecross[elist[j] ^ 1] = ecross[elist[j]] = 1;
		}
	}
	
	// Number faces
	for (fn = 1, i = 2; fn <= m - n + 2; ++fn) {
		for (; i <= epn && fid[i]; ++i);
		// fprintf(stderr, "%d: %d(%d)\n", fn, i, ep[i].to);
		fid[i] = fn;
		vlist[fn].push_back(ep[i].to);
		if (vonslit[ep[i].to] && ecross[i] && ecross[suc[i]]) crossfv[fn][ep[i].to] = 1;
		for (j = suc[i]; j != i; j = suc[j]) {
			// if (j != 0) fprintf(stderr, " -> %d(%d)\n", j, ep[j].to), fflush(stderr);
			fid[j] = fn;
			vlist[fn].push_back(ep[j].to);
			if (vonslit[ep[j].to] && ecross[j] && ecross[suc[j]]) crossfv[fn][ep[j].to] = 1;
		}
	}

	// Special case: a cut vertex on the s-t slit results in ans = 0
	for (u = pre[t]; u != s; u = pre[u]) {
		for (i = headp[u]; i; i = ep[i].next) {
			if (crossfv[fid[i ^ 1]][u] && ecross[i ^ 1] == 0 && ecross[suc[i ^ 1]] == 0) {
				puts("0.000000000000000000");
				return 0;
			}
		}
	}

	// for (i = 2; i <= epn; ++i) fprintf(stderr, "E %d: %d, -> %d, suc = %d\n", i, ecross[i], ep[i].to, suc[i]);
	// for (fn = 1; fn <= m - n + 2; ++fn) for (i = 1; i <= n; ++i) if (crossfv[fn][i]) fprintf(stderr, "F %d <-> V %d\n", fn, i);
	
	// Add dual edges
	for (i = 1; i <= m; ++i) {
		u = fid[i << 1];
		v = fid[i << 1 | 1];
		ed[++edn] = (Edge){cap[i], v, headd[u]};
		headd[u] = edn;
		ed[++edn] = (Edge){cap[i], u, headd[v]};
		headd[v] = edn;
	}

	// Find the minimal cycle by enumerating the start of the cycle
	for (i = 1; i <= n; ++i) {
		if (i == s || i == t) continue;
		// fprintf(stderr, "===%d===\n", i);
		memset(vis, 0, sizeof(vis));
		memset(marked, 0, sizeof(marked));
		for (u = 1; u <= m + 2; ++u) for (du = 0; du < 9; ++du) dis[u][du][0] = dis[u][du][1] = 1e200;
		h.clear();
		dis[i][0][0] = 0;
		h.insert((State){0, i, 0, 0});
		
		while (!h.empty()) {
			now = h.top();
			h.pop();
			u = now.node;
			du = now.destr;
			cu = now.cross;
			if (u == s || u == t || marked[u][du][cu]) continue;
			// fprintf(stderr, "[%d][%d][%d] = %Lf\n", u, du, cu, dis[u][du][cu]);
			if (u == i && cu == 1) {
				cmin(ans, dis[u][du][cu]);
				break;
			}
			marked[u][du][cu] = 1;
			if (u > n) {			// Face
				fn = u - n;
				// Face to face
				for (j = headd[fn]; j; j = ed[j].next) {
					v = ed[j].to + n;
					cv = cu ^ eonslit[j];
					if (dis[v][du][cv] > dis[u][du][cu] + ed[j].w) {
						// fprintf(stderr, "\t-[%Lf]-> (%d, %d, %d)\n", ed[j].w, v, du, cv);
						dis[v][du][cv] = dis[u][du][cu] + ed[j].w;
						h.insert((State){dis[v][du][cv], v, du, cv});
					}
				}
				// Face to vertex
				for (vecint::iterator it = vlist[fn].begin(); it != vlist[fn].end(); ++it) {
					v = *it;
					cv = cu ^ crossfv[fn][v];
					// fprintf(stderr, "\t-?-> (%d, %d, %d) <%Lf>\n", v, du, cv, dis[v][du][cv]);
					if (dis[v][du][cv] > dis[u][du][cu]) {
						// fprintf(stderr, "\t-0-> (%d, %d, %d)\n", v, du, cv);
						dis[v][du][cv] = dis[u][du][cu];
						h.push_front((State){0, v, du, cv});
					}
				}
			}
			else {					// Vertex
				// Vertex to face
				if (du < l) {
					for (j = headp[u]; j; j = ep[j].next) {
						fn = fid[j];
						v = fn + n;
						dv = du + 1;
						cv = cu ^ crossfv[fn][u];
						// fprintf(stderr, "\t-> [%d(fn = %d)][%d][%d] (%Lf)\n", v, fn, dv, cv, dis[v][dv][cv]);
						if (dis[v][dv][cv] > dis[u][du][cu]) {
							// fprintf(stderr, "\t-0-> (%d, %d, %d)\n", v, dv, cv);
							dis[v][dv][cv] = dis[u][du][cu];
							h.push_front((State){0, v, dv, cv});
						}
					}
				}
			}
		}
	}

	fflush(stderr);
	
	printf("%.18Lf\n", ans);
	return 0;
}
