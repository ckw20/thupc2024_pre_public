#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int MAXN = 5e3 + 5;

int p[MAXN];

int main(void)
{
	int n;
	scanf("%d",&n);
	for(int i=1; i<=n; ++i)
		scanf("%d",&p[i]);
	
	vector< array<int,4> > ans;
	
	auto OP = [&] (int i,int j,int ii,int jj)// 1 <= i <= j < ii <= jj <= n
	{
		ans.push_back({i, j, ii, jj});
		rotate(p+i, p+j+1, p+jj+1);
		rotate(p+i, (p+i) + (ii-(j+1)), (p+i) + (jj-(j+1)) + 1);
	};
	
	p[n+1] = n+1;
	
	while(1)
	{
		int l = 1;
		while(l<=n && p[l] == l) ++l;
		if(l > n) break;
		
		int r = find(p+1, p+n+1, l) - p - 1;
		
		int k = max_element(p+l, p+r+1) - p;
		int to = find(p+1, p+n+2, p[k]+1) - p;
		
		OP(l, k, r+1, to-1);
	}
	
	printf("%d\n",(int)ans.size());
	for(auto t: ans)
		printf("%d %d %d %d\n",t[0],t[1],t[2],t[3]);
	return 0;
}
