#define FOR_LINUX
#include"testlib.h"
#include<bits/stdc++.h>
using namespace std;

#define ld long double
const ld eps = 1e-8, pi = acos(-1);
double myReadDouble(double minv, double maxv, string variablename){
	string str = inf.readToken();
	int dotpos = str.find('.');
	ensuref(dotpos != string::npos, (variablename + ": Expected double, but find no dot.").c_str());
	string fir(str.begin(), str.begin() + dotpos) , end(str.begin() + dotpos + 1, str.end());
	ensuref(end.size() == 4, (variablename + ": Expected 4 decimal digits, but find " + to_string(end.size())).c_str());
	double ans = 0;
	for(auto t : fir){
		ensuref(isdigit(t), (variablename + ": Expected digit, but find " + t).c_str());
		ans = ans * 10 + t - '0';
	}
	double base = 1;
	for(auto t : end){
		ensuref(isdigit(t), (variablename + ": Expected digit, but find " + t).c_str());
		base /= 10; ans += base * (t - '0');
	}
	ensuref(minv - eps <= ans && ans <= maxv + eps, (variablename + ": " + to_string(ans) + " not in [" + to_string(minv) + "," + to_string(maxv) + "]").c_str());
	return ans;
}

const int _ = 3003;
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
}point[_]; ld q[_]; int u[_], v[_];
comp normalize(comp X){return X / X.len();}

namespace dsu{
	int fa[_];
	void init(){for(int i = 1 ; i <= N ; ++i) fa[i] = i;}
	int find(int x){return fa[x] == x ? x : (fa[x] = find(fa[x]));}
	void merge(int x, int y){fa[find(x)] = find(y);}
	void check_connectivity(){for(int i = 1 ; i <= N ; ++i) ensuref(find(1) == find(i), "graph not connected");}
}
bool in(int edgeid, comp vertex){
	//need to ensure that, vertex is in the same circle as edgeid.
	return (vertex - point[u[edgeid]]).len() < eps || 
	       (vertex - point[v[edgeid]]).len() < eps || 
		   (vertex - point[u[edgeid]]) * (vertex - point[v[edgeid]]) / (vertex - point[u[edgeid]]).len() / (vertex - point[v[edgeid]]).len() < eps;
}

void run(int c){
	registerValidation();
	N = inf.readInt(3, 1000, "N"); inf.readSpace();
	M = inf.readInt(2, N * (N - 1) / 2, "M"); inf.readSpace();
	L = inf.readInt(1, min(N - 2, 8), "L"); inf.readSpace();
	s = inf.readInt(1, N, "s"); inf.readSpace();
	t = inf.readInt(1, N, "t"); inf.readEoln();
	ensuref(s != t, "s = t");
	R = myReadDouble(1, 1e3, "R"); inf.readSpace();
	K = myReadDouble(1, 1e3, "K"); inf.readEoln();
	for(int i = 1 ; i <= N ; ++i){
		ld a = myReadDouble(0, 1, "a") * pi; inf.readSpace();
		ld b = myReadDouble(0, 2 - eps, "b") * pi; inf.readSpace();
		point[i] = comp(sin(a) * cos(b), sin(a) * sin(b), cos(a));
		q[i] = myReadDouble(1, 1e3, "q"); inf.readEoln();
	}
	for(int i = 1 ; i <= N ; ++i)
		for(int j = i + 1 ; j <= N ; ++j)
			ensuref((point[i] - point[j]).len() > eps, "multiple points");
	set<pair<int,int>> edgeset; dsu::init();
	for(int i = 1 ; i <= M ; ++i){
		u[i] = inf.readInt(1, N, "u"); inf.readSpace();
		v[i] = inf.readInt(1, N, "v"), inf.readEoln();
		ensuref(u[i] != v[i], "self loop");
		if(u[i] > v[i]) swap(u[i], v[i]);
		ensuref(edgeset.find(make_pair(u[i], v[i])) == edgeset.end(), "duplicate edges");
		ensuref((point[u[i]] - point[v[i]]).len() < 2 * R - eps, "antipodal points in one edge");
		edgeset.insert(make_pair(u[i], v[i]));
		dsu::merge(u[i], v[i]);
	}
	dsu::check_connectivity();
	for(int i = 1 ; i <= M ; ++i)
		for(int j = i + 1 ; j <= M ; ++j){
			map < int , int > cnt;
			for(auto t : {u[i], v[i], u[j], v[j]}) ++cnt[t];
			comp linedir = (point[u[i]] % point[v[i]]) % (point[u[j]] % point[v[j]]);
			if(cnt.size() == 4){
				if(linedir.len() < eps){
					//in the same circle
					ensuref(!(in(i, u[j]) || in(i, v[j]) || in(j, u[i]) || in(j, v[i])), "intersection %d %d", i, j);
				}else{
					linedir = normalize(linedir);
					ensuref(!(in(i, linedir) && in(j, linedir)), "intersection %d %d", i, j);
					ensuref(!(in(i, -linedir) && in(j, -linedir)), "intersection %d %d", i, j);
				}
			}else{
				ensuref(cnt.size() == 3, "???");
				if(linedir.len() < eps){
					vector<int>fin{u[i],v[i],u[j],v[j]};
					for(int k = 0 ; k < fin.size() ; ++k)
						if(cnt[fin[k]] == 1)
							ensuref(!in(k < 2 ? j : i , point[fin[k]]), "intersection %d %d", i, j);
				}
			}
		}
	inf.readEof();
	fclose(stdin);
	cerr << c << " fin" << endl;
}

const int CASE = 33 , SAMPLE = 2;

int main(){
	for(int i = 1 ; i <= SAMPLE ; ++i){
		freopen(("../down/" + to_string(i) + ".in").c_str(), "r", stdin);
		run(i);
	}
	for(int i = 1 ; i <= CASE ; ++i){
		freopen(("../data/" + to_string(i) + ".in").c_str(), "r", stdin);
		run(i);
	}
	return 0;
}