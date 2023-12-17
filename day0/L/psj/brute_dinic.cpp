#include<bits/stdc++.h>
using namespace std;

#define db double
#define eps 1e-9
namespace flow{
	const int _ = 1e5 + 7; struct Edge{int end , upEd; db f;}Ed[_]; 
	int head[_] , cntEd = 1 , S , T , N , M; db ans;
	void addEd(int a , int b , db c){Ed[++cntEd] = (Edge){b , head[a] , c}; head[a] = cntEd;}
	void addE(int a , int b , db c){addEd(a , b , c); addEd(b , a , c);}

	int dep[_] , cur[_]; queue < int > q; bool novis[_];
	bool bfs(){
		memset(dep , 0 , sizeof(int) * (N + 1)); while(!q.empty()) q.pop();
		dep[S] = 1; q.push(S);
		while(!q.empty()){
			int t = q.front(); q.pop();
			for(int i = head[t] ; i ; i = Ed[i].upEd)
				if(!dep[Ed[i].end] && Ed[i].f > eps * ans && !novis[Ed[i].end]){
					dep[Ed[i].end] = dep[t] + 1; q.push(Ed[i].end);
					if(Ed[i].end == T){memcpy(cur , head , sizeof(int) * (N + 1)); return 1;}
				}
		}
		return 0;
	}

	db dfs(int x , db mn){
		if(x == T) return mn;
		db sum = 0;
		for(int &i = cur[x] ; i ; i = Ed[i].upEd)
			if(dep[Ed[i].end] == dep[x] + 1 && Ed[i].f > ans * eps){
				db t = dfs(Ed[i].end , min(mn - sum , Ed[i].f)); Ed[i].f -= t; Ed[i ^ 1].f += t;
				if((sum += t) >= mn - eps * ans) break;
			}
		return sum;
	}

	void clear(){
		for(int i = 2 ; i < cntEd ; i += 2)
			Ed[i].f = Ed[i + 1].f = (Ed[i].f + Ed[i + 1].f) / 2;
	}
	db dinic(){ans = 1e-8; while(bfs()){ans += dfs(S, 1e20);} flow::clear(); return ans;}
}using flow::addE, flow::dinic;

const int _ = 1003; const db pi = acos(-1);
int N , M; db R, K , q[_], pos[_][3];
db len(db x, db y, db z){return sqrt(x*x+y*y+z*z);}
db dist(int x, int y){
	db angle = acos((pos[x][0] * pos[y][0] + pos[x][1] * pos[y][1] + pos[x][2] * pos[y][2]) / len(pos[x][0], pos[x][1], pos[x][2]) / len(pos[y][0], pos[y][1], pos[y][2]));
	db dist = R * angle;
	return K * q[x] * q[y] / dist / dist;
}

int main(){
	cin >> N >> M >> flow::S >> flow::T >> R >> K; flow::N = N;
	for(int i = 1 ; i <= N ; ++i){
		db a, b; cin >> a >> b >> q[i]; a *= pi; b *= pi;
		pos[i][0] = R * sin(a) * cos(b);
		pos[i][1] = R * sin(a) * sin(b);
		pos[i][2] = R * cos(a);
	}
	for(int i = 1 ; i <= M ; ++i){
		int u, v; cin >> u >> v;
		addE(u, v, dist(u, v));
	}
	db minans = 1e50;
	for(int i = 1 ; i <= N ; ++i)
		if(i != flow::S && i != flow::T){
			flow::novis[i] = 1;
			minans = min(minans, dinic());
			flow::novis[i] = 0;
		}
	cout << fixed << setprecision(10) << minans;
	return 0;
}
