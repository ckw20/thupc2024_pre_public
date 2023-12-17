#include<bits/stdc++.h>
using namespace std;

#define ld double
const int _ = 2e5 + 3; const ld pi = acos(-1), eps = 1e-9;
int N, M, L, s, t; ld R, K;
struct comp{
	ld x, y, z; comp(ld _x = 0, ld _y = 0, ld _z = 0){x = _x; y = _y; z = _z;}
	ld len(){return sqrt(x * x + y * y + z * z);}
	friend comp operator +(comp p, comp q){return comp(p.x + q.x, p.y + q.y, p.z + q.z);}
	friend comp operator -(comp p, comp q){return comp(p.x - q.x, p.y - q.y, p.z - q.z);}
	friend comp operator -(comp p){return comp() - p;}
	friend comp operator *(comp p, ld q){return comp(p.x * q, p.y * q, p.z * q);}
	friend comp operator /(comp p, ld q){return p * (1 / q);}
	friend ld operator *(comp p, comp q){return p.x * q.x + p.y * q.y + p.z * q.z;}
	friend comp operator %(comp p, comp q){return comp(p.y * q.z - p.z * q.y, p.z * q.x - p.x * q.z, p.x * q.y - p.y * q.x);}
}point[_]; ld q[_]; int u[_], v[_]; bool imp[_];
ld angle(comp p, comp q){return acos(p * q / p.len() / q.len());}

namespace dsu{
	int fa[_] , label[_] , cntlabel;
	int find(int x){return fa[x] == x ? x : (fa[x] = find(fa[x]));}
	void merge(int p, int q){fa[find(p)] = find(q);}
	void labelit(int x){label[x] = ++cntlabel;}
	int findlabel(int x){return label[find(x)];}
}using dsu::find, dsu::merge, dsu::labelit, dsu::findlabel;

namespace graph{
	vector<pair<int,ld>> nxt[_]; int tot;
	void addEd(int p, int q, ld w){nxt[p].push_back(make_pair(q, w));}
	void addE(int p, int q, ld w){addEd(p, q, w); addEd(q, p, w);}

	ld dist[_]; priority_queue<pair<ld, int>> q; 
	ld sssp(int s, int t){
		fill(dist + 1, dist + tot + 1, 1e18);
		q.push(make_pair(dist[s] = 0, s));
		while(!q.empty()){
			auto [d, u] = q.top(); q.pop();
			if(dist[u] < d - eps) continue;
			for(auto [t,w]: nxt[u])
				if(dist[t] > dist[u] + w){q.push(make_pair(-(dist[t] = dist[u] + w), t));}
		}
		return dist[t];
	}
}using graph::addEd, graph::addE, graph::sssp;

int main(){
	L = 1; ios::sync_with_stdio(0); cin >> N >> M >> L >> s >> t >> R >> K;
	for(int i = 1 ; i <= N ; ++i){
		ld a, b; cin >> a >> b >> q[i]; a *= pi; b *= pi;
		point[i] = comp(sin(a) * cos(b), sin(a) * sin(b), cos(a)) * R;
	}
	for(int i = 1 ; i <= M ; ++i) cin >> u[i] >> v[i];
	
	//find s~t path
	static vector<int> nxt[_]; static int pre[_];
	for(int i = 1 ; i <= M ; ++i){nxt[u[i]].push_back(i); nxt[v[i]].push_back(i);}
	queue < int > que; pre[s] = -1; que.push(s);
	while(!que.empty()){
		int r = que.front(); que.pop();
		for(auto p: nxt[r]) if(!pre[u[p] + v[p] - r]){pre[u[p] + v[p] - r] = p; que.push(u[p] + v[p] - r);}
	}
	int fin = t; while(fin != s){int e = pre[fin]; imp[e] = 1; fin = u[e] + v[e] - fin;}

	//get all faces
	static vector < pair < comp , int > > ordered_edge[_];
	for(int i = 2 ; i <= 2 * M + 1 ; ++i) dsu::fa[i] = i;
	for(int i = 1 ; i <= N ; ++i){
		vector < pair < comp , int > > &edges = ordered_edge[i];
		for(int j = 1 ; j <= M ; ++j)
			if(u[j] == i) edges.emplace_back(point[v[j]] - point[u[j]], 2 * j);
			else if(v[j] == i) edges.emplace_back(point[u[j]] - point[v[j]], 2 * j + 1);
		comp unit = point[i] / R;
		for(auto &[c, d] : edges) c = c - unit * (c * unit);
		auto getf = [&](pair<comp,int>p){
			pair<bool,ld>fp((p.first % edges[0].first) * unit > -eps, p.first * edges[0].first / p.first.len());
			if(fp.first == 0) fp.second *= -1;
			return fp;
		};
		sort(edges.begin() + 1, edges.end() , [&](pair<comp,int>p,pair<comp,int>q){
			auto fp = getf(p), fq = getf(q);
			return fp > fq;
		});
		for(int i = 0 ; i < edges.size() ; ++i)
			merge(edges[i].second ^ 1, edges[(i + 1) % edges.size()].second);
	}
	for(int i = 2 ; i <= 2 * M + 1 ; ++i) if(find(i) == i) labelit(i);

	//build the graph
	int tot = dsu::cntlabel; graph::tot = 2 * (L + 1) * tot + 2 * N * L;
	for(int i = 1 ; i <= M ; ++i){
		int u = findlabel(2 * i), v = findlabel(2 * i + 1); bool f = imp[i];
		ld w = K * q[::u[i]] * q[::v[i]] / pow(R * angle(point[::u[i]], point[::v[i]]), 2);
		for(int i = 0 ; i <= L ; ++i)
			for(int j = 0 ; j < 2 ; ++j)
				addE((2 * i + j) * tot + u, (2 * i + (j ^ f)) * tot + v, w);
	}
	int cur = 2 * (L + 1) * tot;
	for(int i = 1 ; i <= N ; ++i){
		if(i != s && i != t){
			vector < int > pot[2]; int c = 0;
			for(auto [x, y]: ordered_edge[i])
				pot[c ^= imp[y >> 1]].push_back(findlabel(y ^ 1));
			for(int j = 0 ; j < L ; ++j){
				int id[2] = {++cur, ++cur};
				for(int p = 0 ; p < 2 ; ++p)
					for(int q = 0 ; q < 2 ; ++q)
						for(auto x : pot[p]){
							addEd((2 * j + q) * tot + x , id[p ^ q], 0);
							addEd(id[p ^ q], (2 * (j + 1) + q) * tot + x, 0);
						}
			}
		}
	}
	ld ans = 1e18; for(int i = 1 ; i <= tot ; ++i) ans = min(ans, sssp(i, (2 * L + 1) * tot + i));
	cout << fixed << setprecision(10) << ans << endl; return 0;
}