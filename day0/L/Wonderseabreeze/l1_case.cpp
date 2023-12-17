#include <cstdio>
#include <cmath>
#include <cstring>
#include <utility>
#include <algorithm>
using namespace std;
#define cmin(_a, _b) (_a > (_b) ? _a = (_b) : 0)
typedef pair<int, int> State;
const long double pi = acosl(-1);
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
} p[1008], tmp;
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
	void pr() const {
		fprintf(stderr, "===\n");
		fprintf(stderr, "%Lf %Lf %Lf\n", a[0][0], a[0][1], a[0][2]);
		fprintf(stderr, "%Lf %Lf %Lf\n", a[1][0], a[1][1], a[1][2]);
		fprintf(stderr, "%Lf %Lf %Lf\n", a[2][0], a[2][1], a[2][2]);
		fprintf(stderr, "===\n");
	}
} rt[1008];
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
	return rotate_z(phi) * rotate_y(-theta) * rotate_z(-phi);
}
struct Edge {
	long double w;
	int to;
	int next;
} ep[6003], ed[6003];
long double theta[1008], phi[1008], q[1008], rot_theta[1008], dis[2016][2], cap[3006];
int headp[6003], headd[6003], suc[6003], elist[1008], fid[6003], epn = 1, edn = 1;
int removed[3006], vis[1008], marked[2016][2], que[1008], pre[1008], pledge[1008], cut[3006];
bool cmp(const int &i, const int &j){
	return rot_theta[ep[i].to] < rot_theta[ep[j].to];
}
bool heapcmp(const State &i, const State &j){
	return dis[i.first][i.second] == dis[j.first][j.second] \
		? (i.first == j.first ? (i.second < j.second) : i.first < j.first) \
		: dis[i.first][i.second] > dis[j.first][j.second];
}
struct Heap {
	State h[12006];
	int tot;
	Heap() {
		tot = 0;
	}
	void insert(State s) {
		h[++tot] = s;
		push_heap(h + 1, h + tot + 1, heapcmp);
		return ;
	}
	void pop() {
		pop_heap(h + 1, h + tot + 1, heapcmp);
		--tot;
		return ;
	}
	State top() const {
		return h[1];
	}
	bool empty() const {
		return tot == 0;
	}
	void clear() {
		tot = 0;
		return ;
	}
} h;
int main(){
	int n, m, s, t, i, j, u, v, x, y, fn, cnt, qh, qt;
	long double r, k, ans = 1e200, arclen;
	State now;
	scanf("%d %d %d %d", &n, &m, &s, &t);
	scanf("%Lf %Lf", &r, &k);
	for (i = 1; i <= n; ++i) {
		scanf("%Lf %Lf %Lf", &theta[i], &phi[i], &q[i]);
		theta[i] *= pi;
		phi[i] *= pi;
		p[i] = Point(r, theta[i], phi[i]);
	}
	for (i = 1; i <= m; ++i) {
		scanf("%d %d", &u, &v);
		arclen = r * acosl(p[u] * p[v] / r / r);
		cap[i] = k * q[u] * q[v] / arclen / arclen;
		ep[++epn] = (Edge){cap[i], v, headp[u]};
		headp[u] = epn;
		ep[++epn] = (Edge){cap[i], u, headp[v]};
		headp[v] = epn;
	}
	
	for (i = 1; i <= n; ++i) {
		rt[i] = rotate_to_north(theta[i], phi[i]);
		cnt = 0;
		for (j = headp[i]; j; j = ep[j].next) {
			elist[++cnt] = j;
			v = ep[j].to;
			tmp = rt[i] * p[v];
			//fprintf(stderr, "%d: %Lf %Lf %Lf\n", v, tmp.x, tmp.y, tmp.z);
			rot_theta[v] = atan2l(tmp.y, tmp.x);
		}
		sort(elist + 1, elist + cnt + 1, cmp);
		elist[0] = elist[cnt];
		for (j = 1; j <= cnt; ++j) {
			//fprintf(stderr, "%d(%Lf)%c", elist[j], rot_theta[ep[elist[j]].to], " \n"[j == cnt]);
			suc[elist[j] ^ 1] = elist[j - 1];
		}
	}
	//for (i = 2; i <= epn; ++i) fprintf(stderr, " %d -> %d \n", i, suc[i]);
	//fprintf(stderr, "GG\n"); fflush(stderr);
	
	for (fn = 1; fn <= m - n + 2; ++fn) {
		for (i = 2; i <= epn && fid[i]; ++i);
		//fprintf(stderr, "%d: %d\n", fn, i);
		fid[i] = fn;
		for (j = suc[i]; j != i; j = suc[j]) {
			//if (j != 0) fprintf(stderr, " -> %d\n", j);
			fid[j] = fn;
		}
	}
	
	for (i = 1; i <= m; ++i) {
		u = fid[i << 1];
		v = fid[i << 1 | 1];
		ed[++edn] = (Edge){cap[i], v, headd[u]};
		headd[u] = edn;
		ed[++edn] = (Edge){cap[i], u, headd[v]};
		headd[v] = edn;
	}
	
	for (i = 1; i <= n; ++i) {
		if (i == s || i == t) continue;
		memset(removed, 0, sizeof(removed));
		memset(vis, 0, sizeof(vis));
		for (j = headp[i]; j; j = ep[j].next) {
			removed[j >> 1] = 1;
		}
		vis[s] = 1;
		que[qh = qt = 0] = s;
		while (qh <= qt) {
			u = que[qh++];
			vis[u] = 1;
			for (j = headp[u]; j; j = ep[j].next) {
				if (removed[j >> 1] == 0 && vis[v = ep[j].to] == 0) {
					que[++qt] = v;
					vis[v] = 1;
					pre[v] = u;
					pledge[v] = j;
					if (v == t) break;
				}
			}
			if (j) break;
		}
		if (qh > qt) {
			ans = 0;
			break;
		}
		memset(cut, 0, sizeof(cut));
		for (u = t; u != s; u = pre[u]) cut[pledge[u] >> 1] = 1;
		
		memset(marked, 0, sizeof(marked));
		for (u = 1; u <= m - n + 2; ++u) dis[u][0] = dis[u][1] = 1e200;
		h.clear();
		for (j = headp[i]; j; j = ep[j].next) {
			dis[fid[j]][0] = 0;
			h.insert(State {fid[j], 0});
		}
		
		while (!h.empty()) {
			now = h.top();
			h.pop();
			u = now.first;
			x = now.second;
			if (marked[u][x]) continue;
			// fprintf(stderr, "[%d] (%d, %d)\n", i, u, x);
			marked[u][x] = 1;
			for (j = headd[u]; j; j = ed[j].next) {
				if (removed[j >> 1] == 0) {
					v = ed[j].to;
					y = x ^ cut[j >> 1];
					// fprintf(stderr, "  (%d, %d)[%Lf, %Lf] -> (%d, %d)[%Lf]\n", u, x, dis[u][x], ed[j].w, v, y, dis[v][y]);
					if (dis[u][x] + ed[j].w < dis[v][y]) {
						// fprintf(stderr, "  (%d, %d) -> (%d, %d)\n", u, x, v, y);
						dis[v][y] = dis[u][x] + ed[j].w;
						h.insert(State {v, y});
					}
				}
			}
		}
		
		for (j = headp[i]; j; j = ep[j].next) {
			cmin(ans, dis[fid[j]][1]);
		}
	}
	
	printf("%.18Lf\n", ans);
	return 0;
}
