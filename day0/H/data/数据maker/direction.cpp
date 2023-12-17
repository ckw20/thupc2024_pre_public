#include<bits/stdc++.h>
#define ll long long 
#define dd double 
#define ull unsigned ll
#define LL __int128
#define siz(A) ((int)A.size())
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
	static char buf[1<<16],*s=buf,*t=(buf+(1<<16));
	(op||((*s++=c)&&(s==t)))&&(fwrite(buf,1,s-buf,stdout),s=buf);
}
void wt(int x)
{
	if(x>9)wt(x/10);
	pc('0'+x%10,0);
}
void wts(int x,char op)
{
	if(x<0)pc('-',0),x=-x;
	wt(x),pc(op,0);
}
char ST;
const int xx=3e5+5,mod=998244353;
int n;
vector<array<int,2> >v[xx];
int f[xx][2],pf[xx],sf[xx];
// 0 指向父亲, 1 指向儿子。 
void dfs(int x,int y)
{
	sort(v[x].begin(),v[x].end());
	
	for(auto it:v[x])if(it[1]!=y)dfs(it[1],x);
	int id=-1;
	for(int i=0;i<siz(v[x]);i++)if(v[x][i][1]==y)id=i;
	pf[0]=1;
	for(int i=0;i<siz(v[x]);i++)
	{
		if(i==id)pf[i+1]=pf[i];
		else pf[i+1]=1ll*pf[i]*f[v[x][i][1]][1]%mod;
	}
	sf[siz(v[x])]=1;
	for(int i=siz(v[x])-1;i>=0;i--)
	{
		if(i==id)sf[i]=sf[i+1];
		else sf[i]=1ll*sf[i+1]*f[v[x][i][1]][0]%mod;
	}
	
	if(x==1)
	{
		ll ans=0;
		for(int i=0;i<=siz(v[x]);i++)ans+=1ll*pf[i]*sf[i],ans%=mod;
		cout<<ans<<"\n";
		exit(0);
	}
	
	for(int i=0;i<=siz(v[x]);i++)
		f[x][i<=id]=(f[x][i<=id]+1ll*pf[i]*sf[i])%mod;
//	cerr<<x<<" "<<f[x][0]<<" "<<f[x][1]<<"%%\n";
}
char ED;
int main(){
	cerr<<abs(&ST-&ED)/1024.0/1024<<"\n";
	freopen("direction.in","r",stdin);
	freopen("direction.out","w",stdout);
	n=read();
	for(int i=1;i<n;i++)
	{
		int a=read(),b=read();
		v[a].push_back({i,b});
		v[b].push_back({i,a});
	}
	dfs(1,0);
	
	pc('1',1);
	return 0;
}

