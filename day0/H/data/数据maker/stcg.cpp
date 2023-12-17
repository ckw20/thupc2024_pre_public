#include<bits/stdc++.h>
namespace ifzw{
#define ll long long
#define dd double
#define LL __int128
//#define ull unsigned ll
#define uLL __uint128_t
using namespace std;
char gc(){static char buf[1<<16],*s,*t;if(s==t){t=(s=buf)+fread(buf,1,1<<16,stdin);if(s==t)return EOF;}return *s++;}
#define getchar gc
uLL read()
{
	char c;
	LL w=1;
	while((c=getchar())>'9'||c<'0')if(c=='-')w=-1;
	LL ans=c-'0';
	while((c=getchar())>='0'&&c<='9')ans=(ans<<1)+(ans<<3)+c-'0';
	return ans*w;
}
void pc(char c,int op)
{
	static char buf[1<<16],*s=buf,*t=(buf+(1<<16));
	(op||((*s++=c)&&(s==t)))&&(fwrite(buf,1,s-buf,stdout),s=buf);
}
void wt(uLL x)
{
	if(x>9)wt(x/10);
	pc('0'+x%10,0);
}
void wts(uLL x,char op)
{
	if(x<0)pc('-',0),x=-x;
	wt(x),pc(op,0);
}
//有点害怕，就用 uLL 吧。 
const int xx=123;
int n,m,k;
uLL a[xx];
vector<uLL>bac[50];//数字 =1 表示要应用这一位。 
uLL ans;
//其实可以直接描述为一个最优化剪枝，需要处理如果全满必定不要，不然优先要。 
int lim;
void dfs(int I,uLL tt,int ct)
{
	if(I==-1)
	{
		ans=max(ans,tt);
		return;
	}
	if(tt+n*((((uLL)1)<<(I+1))-1)<ans)return;
	int mx=0;
	for(int i=0;i<(1<<ct);i++)
	{
		int lin=0;
		for(int j=0;j<(1<<ct);j++)
			for(auto &it:bac[j])
				lin+=(it>>I&1)^__builtin_parity(j&i);
		mx=max(mx,lin);
	}
	if(ct<k&&mx!=n)//要 
	{
		vector<vector<uLL>>info(1<<ct);
		for(int i=0;i<(1<<ct);i++)info[i]=bac[i];
		for(int i=0;i<(1<<ct);i++)bac[i+(1<<ct)].clear();//注意。 
		for(int i=0;i<(1<<ct);i++)
		{
			vector<uLL>lin;
			for(auto it:bac[i])
				if(!(it>>I&1))bac[i+(1<<ct)].push_back(it);
				else lin.push_back(it);
			bac[i]=lin;
		}
		dfs(I-1,(((uLL)1)<<I)*n+tt,ct+1);
		for(int i=0;i<(1<<ct);i++)bac[i]=info[i];
	}
	//不要。 
	dfs(I-1,(((uLL)1)<<I)*mx+tt,ct);
}
//namespace bf
//{
//	void solve()
//	{
//		
//	}
//}
//瞪出来了？ 
//好。 
int main(){
	freopen("lin.in","r",stdin);
	freopen("lin.out","w",stdout);
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;i++)
	{
		a[i]=read();
//		for(int j=0;j<m;j++)cout<<(int)(a[i]>>j&1);
//		puts("");
		if(!(a[i]< (((uLL)1)<<m)))
		{
			a[i]-=(((uLL)1)<<m);
			a[i]^=a[i-1];
		}
//		wts(a[i],'\n'),wts((((uLL)1)<<m),'\n'),pc('1',1),exit(0);
//		assert(a[i]< (((uLL)1)<<m));
//		for(int j=62;j<=99;j++)
//		cout<<(int)(a[i]>>j&1)<<"\n";
	}
	wts(n,' '),wts(m,' '),wts(k,'\n');
	for(int i=1;i<=n;i++)wts(a[i],' ');
	
	pc('1',1);
	exit(0);
	// check 能否组合成功。 
	//划分成多个集合。 
	for(int i=1;i<=n;i++)bac[0].push_back(a[i]);
	dfs(m-1,0,0);
	/*
	for(int i=1;i<=n;i++)info[0].push_back(a[i]);
	int ct=0;
	//反正就是不高，好像有个 m 实际上是 k 。 
	uLL tt=0;
	for(int i=m-1;i>=0;i--)
	{
		int cr=0;
		for(int j=1;j<=n;j++)
			if(!(a[j]>>i&1))cr=1;
		if(cr)
		{
			for(int i=0;i<(1<<ct);i++)
				bck[i]=info[i];
			lim=max(i-8,0);
			dfs(i,tt,ct);
			if(ct+1>k)break;
			for(int i=0;i<(1<<ct);i++)
			{
				vector<uLL>lin;
				for(auto it:info[i])
					if(!(it>>i&1))info[i+(1<<ct)].push_back(it);
					else lin.push_back(it);
				info[i]=lin;
			}
			++ct;
		}
		tt+=(((uLL)1)<<i)*n;
	}
	if(ct<=k)ans=n*tt;*/
	wts(ans,'\n');
	pc('1',1);
	return 0;
}


}signed main(){return ifzw::main();}
