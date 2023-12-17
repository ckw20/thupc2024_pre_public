#include<bits/stdc++.h>
using namespace std;

#define int long long
#define vi vector<int>
#define pii pair<int,int>
const int _ = 5e5 + 7; int N , K; vi nxt[_];

int val[_], mrk[_], sz[_], ch[_][2], cntnode;
int newnode(){sz[++cntnode] = 1; return cntnode;}
void mark(int x, int v){val[x] += v; mrk[x] += v;}
void down(int x){if(mrk[x]){mark(ch[x][0], mrk[x]); mark(ch[x][1], mrk[x]); mrk[x] = 0;}}
int merge(int p, int q){
	if(!p || !q) return p + q;
	if(val[p] < val[q]) swap(p, q);
	down(p); ch[p][1] = merge(ch[p][1], q);
	if(sz[ch[p][0]] < sz[ch[p][1]]) swap(ch[p][0], ch[p][1]);
	sz[p] = sz[ch[p][0]] + sz[ch[p][1]] + 1; return p;
}
int del(int x){down(x); sz[x] = 1; int newrt = merge(ch[x][0], ch[x][1]); ch[x][0] = ch[x][1] = 0; return newrt;}
pii prune(int rt, int tarsz){
	int newrt = 0; while(sz[rt] > tarsz){int tmprt = del(rt); newrt = merge(newrt, rt); rt = tmprt;}
	return pii(rt, newrt);
}

struct dat{
	vi rt, tar; int fir;
	dat(){
		if(!(K & 1)){rt = {newnode(), 0}; tar = {K / 2, K / 2};}
		else{rt = {newnode(), 0, 0}; tar = {K / 2 , 1, K / 2};}
		fir = 0;
	}
	void datprune(){
		int tmprt = 0; 
		for(int i = 0 ; i < rt.size() ; ++i){
			auto [x, y] = prune(merge(rt[i], tmprt), tar[i]);
			rt[i] = x; tmprt = y;
		}
	}
	friend void operator +=(dat &p, dat q){p.fir += q.fir; for(int i = 0 ; i < p.rt.size() ; ++i) p.rt[i] = merge(p.rt[i], q.rt[i]);}
	void datmark(){datprune(); fir += K; for(int i = 0 ; i < rt.size() ; ++i) mark(rt[i], -2 + 4 / (rt.size() - 1) * i);}
	int getans(){int ans = fir; for(auto t : rt){while(t){ans += val[t]; t = del(t);}} return ans;}
};

dat dp(int x, int p){
	dat cur; for(auto t : nxt[x]) if(t != p) cur += dp(t, x);
	p ? cur.datmark() : cur.datprune(); return cur;
}

signed main(){
	ios::sync_with_stdio(0); cin.tie(0); cin >> N >> K;
	for(int i = 1 ; i < N ; ++i){int p, q; cin >> p >> q; nxt[p].push_back(q); nxt[q].push_back(p);}
	cout << dp(1, 0).getans();
	return 0;
}