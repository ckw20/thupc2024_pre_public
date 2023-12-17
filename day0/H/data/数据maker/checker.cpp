#include<bits/stdc++.h>
#define ll long long
#define LL __int128
#define ull unsigned ll 
#define dd double
using namespace std;
char gc(){static char buf[1<<16],*s,*t;if(s==t){t=(s=buf)+fread(buf,1,1<<16,stdin);if(s==t)return EOF;}return *s++;}
#define getchar gc
ll read()
{
	char c;
	ll w=1;
	while((c=getchar())>'9'||c<'0')if(c=='-')w=-1;
	ll ans=c-'0';
	while((c=getchar())>='0'&&c<='9')ans=(ans<<1)+(ans<<3)+c-'0';
	return ans*w;
}
void pc(char c,int op)
{
	static char buf[1<<16],*s=buf,*t=buf+(1<<16);
	(op||((*s++=c)&&s==t))&&(fwrite(buf,1,s-buf,stdout),s=buf);
}
void wt(int x)
{
	if(x>9)wt(x/10);
	pc('0'+x%10,0);
}
void wts(int x,char op)
{
	if(x<0)pc('-',0),x=-x;
	wt(x);pc(op,0);
}
const int xx=1e6+5;
//2 mid rate µÄ¼õÉÙ¡£ 
int a[xx],nl,nr;
ll sl[xx],sr[xx];
int lb(int x){return x&-x;}
struct szsz
{
	int lim;
	ll mx[xx];
	void cls(int L){lim=L;for(int i=1;i<=L;i++)mx[i]=-1e9;}
	void add(int x,ll y){for(;x<=lim;x+=lb(x))mx[x]=max(mx[x],y);}
	ll ask(int x){ll ans=0;for(;x;x-=lb(x))ans=max(ans,mx[x]);return ans;}
	int bin(ll x)
	{
		if(x+mx[0]>0)return 0;
		int ans=0;
		for(int i=__lg(max(1,lim));i>=0;i--)
			if(ans+(1<<i)<=lim&&mx[ans+(1<<i)]+x<=0)ans+=(1<<i);
		return ans;
	}
}s1,s2;
bool run()
{
	int tl=0,tr=0,il=s1.bin(sr[0]),ir=s2.bin(sl[0]);
	while(tl!=il||tr!=ir)
	{
		if(tl!=il)++tl,ir=max(ir,s2.bin(sl[tl]));
		if(tr!=ir)++tr,il=max(il,s1.bin(sr[tr]));
	}
	return tl==nl&&tr==nr;
}
bool solve()
{
	if(sl[nl]+sr[nr]>0)return 0;
	s1.cls(nl),s2.cls(nr);
	for(int i=1;i<=nl;i++)s1.add(i,sl[i]);
	for(int i=1;i<=nr;i++)s2.add(i,sr[i]);
	s1.mx[0]=sl[0];
	s2.mx[0]=sr[0];
	if(!run())return 0;
	reverse(sl,sl+nl+1);
	reverse(sr,sr+nr+1);
	s1.cls(nl),s2.cls(nr);
	for(int i=1;i<=nl;i++)s1.add(i,sl[i]);
	for(int i=1;i<=nr;i++)s2.add(i,sr[i]);
	s1.mx[0]=sl[0];
	s2.mx[0]=sr[0];
	return run();
}
int main(){
	freopen("icey.in","r",stdin);
//	freopen("icey.out","w",stdout);
	int T=read();
	while(T--)
	{
		int n=read(),m=read();
		sl[n+1]=sr[m+1]=0;
		for(int i=1;i<=n;i++)sl[i]=read();
		for(int i=1;i<=m;i++)sr[i]=read();
		nl=n,nr=m;
		if(solve())return 1;
		else return 0;
	}
	pc('1',1);
	return 0;
}
