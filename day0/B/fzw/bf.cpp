#include<bits/stdc++.h>
namespace ifzw{
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
const int xx=5e5+5;
int n,tk;
struct nod{int next,to;}e[xx<<1];
int cnt,h[xx];
void add(int x,int y){cnt++,e[cnt]={h[x],y},h[x]=cnt;}
int siz[xx];
ll f[1005][1005],g[1005];
void dfs(int x,int y)
{
//	cerr<<x<<" "<<y<<"$\n";
	for(int i=h[x];i;i=e[i].next)
	{
		if(e[i].to==y)continue;
		dfs(e[i].to,x);
		for(int j=0;j<=siz[x]+siz[e[i].to];j++)g[j]=1e18;
		for(int j=0;j<=siz[x];j++)
			for(int k=0;k<=siz[e[i].to];k++)
				g[j+k]=min(g[j+k],f[x][j]+f[e[i].to][k]);
		for(int j=0;j<=siz[x]+siz[e[i].to];j++)f[x][j]=g[j];
		siz[x]+=siz[e[i].to];
	}
	f[x][siz[x]+1]=1e18;
	for(int k=siz[x];k>=0;k--)
		f[x][k+1]=min(f[x][k+1],f[x][k]);
	siz[x]++;
	if(x!=1)for(int k=0;k<=siz[x];k++)f[x][k]+=abs(k-(tk-k));//,cerr<<x<<" "<<k<<" "<<f[x][k]<<"$\n";
	
}

char ED;
int main(){
	cerr<<abs(&ST-&ED)/1024.0/1024<<"\n";
//	freopen("a.in","r",stdin);
//	freopen("tree.in","r",stdin);
//	freopen("tree.out","w",stdout);
	n=read(),tk=read();
	for(int i=1;i<n;i++)
	{
		int x=read(),y=read();
		add(x,y),add(y,x);
	}
	dfs(1,0);
	cout<<f[1][tk]<<"\n";
	pc('1',1);
	return 0;
}


}signed main(){return ifzw::main();}
