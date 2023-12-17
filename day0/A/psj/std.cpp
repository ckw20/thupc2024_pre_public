#include<bits/stdc++.h>
using namespace std;

const int _ = 2003; int n, p[_], q[_];
vector < vector < int > > op;
void operate(vector < int > op){
	rotate(p + op[0], p + op[1] + 1, p + op[2]);
	rotate(p + op[0], p + op[2], p + op[3] + 1);
}

int main(){
	ios::sync_with_stdio(0); cin >> n; p[n+1] = n+1;
	for(int i = 1 ; i <= n ; ++i) cin >> p[i];
	while(1){
		int posmx = 0, posy = 0, posx = n+1;
		for(int i = 1 ; i <= n ; ++i){
			if(p[posmx] > p[i] && p[posx] > p[i]) posx = i, posy = posmx;
			if(p[posmx] < p[i]) posmx = i;
		}
		if(posx > n) break;
		int pospx = posy - 1 , pospy = posx + 1;
		while(pospx && p[pospx] != p[posx] - 1) --pospx;
		while(pospy <= n && p[pospy] != p[posy] + 1) ++pospy;
		op.push_back({pospx + 1, posy, posx, pospy - 1});
		operate(op.back());
	}
	cout << op.size() << endl;
	for(auto t: op) cout << t[0] << ' ' << t[1] << ' ' << t[2] << ' ' << t[3] << '\n';
	return 0;
}