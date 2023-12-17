#include<bits/stdc++.h>
using namespace std;

#define int long long
const int _ = 4e5 + 7; int N, a[_], b[_], c[_];

signed main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> N;
	for(int i = 1 ; i <= N ; ++i) cin >> a[i];
	for(int i = 1 ; i <= N ; ++i) cin >> b[i];
	for(int i = 1 ; i <= N ; ++i) cin >> c[i];
	int nc_arb = 0 , nc_fix = 0, c1_arb = 0, c1_fix = 0; vector < int > cleft;
	for(int i = 1 ; i <= N ; ++i)
		if(a[i]){a[i] += c[i]; nc_arb += min(a[i] , b[i]); nc_fix += a[i] - min(a[i], b[i]);}
		else if(b[i]){int num = c[i] + 1 , res = b[i]; c1_arb += min(num, res) - 1; c1_fix += num - min(num, res);}
		else cleft.push_back(c[i]);
	bool flg = nc_arb; if(flg){nc_arb += c1_arb; nc_fix += c1_fix;}
	sort(cleft.rbegin(), cleft.rend());
	for(int i = 1 ; i <= N ; ++i)
		cout << nc_arb + (a[i] ? a[i] - min(a[i], b[i]) : (flg ? c[i] - min(c[i], max(0ll, b[i] - 1)) : 0)) << " \n"[i == N];
	for(int i = 0 ; i < cleft.size() && i < nc_arb ; ++i) nc_fix += cleft[i];
	cout << nc_arb + nc_fix << '\n';
	return 0;
}