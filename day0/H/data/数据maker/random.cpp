#include<bits/stdc++.h>
#define ull unsigned ll 
#define ld long double
#define ll long long
#define LL __int128
#define dd double
using namespace std;
char gc(){static char buf[1<<16],*s,*t;if(s==t){t=(s=buf)+fread(buf,1,1<<16,stdin);if(s==t)return EOF;}return *s++;}
//#define getchar gc
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
    wt(x),pc(op,0);
}
char ST;
random_device R;
mt19937 G(R());
int rd(int l,int r)
{
	return uniform_int_distribution<int>(l,r)(G);
}
const int xx=2e5+5;
int fa[xx];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);
}
char ED;
int main(){
//	cerr<<abs(&ST-&ED)/1024.0/1024<<"\n";
	freopen("a.in","w",stdout);
	freopen("now.in","r",stdin);
	int nid=read();
	int T=5;
	cout<<T<<"\n";
	int k=0;
	while(T--)
	{
		int n=100000;
		cout<<n<<"\n";
		int re=0;
		int D=0;
		ll st=-8e7+G()%123456;
		if(T==0)
		{
			for(int i=1;i<=n;i++)
				cout<<min(1ll*(n-i)*(i-D)-(int)5e7,(ll)1e8)<<" "<<n-i<<"\n";
		}
		else if(T<=3)
		{
			for(int i=1;i<=n;i++)
			{
				st+=re,st=min(st,(ll)1e8);
				if(G()%100==0)++re;
				if(G()%20==0)++re;
				cout<<st<<" "<<n-i<<"\n";
			}
		}
		else 
//		if(T==3)
		{
			for(int i=1;i<=n;i++)
			{
				st+=re,st=min(st,(ll)1e8);
				if(G()%100==0)++re;
				if(G()%20==0)++re;
				cout<<st<<" "<<(n-i+G())%18<<"\n";
			}
		}
//		else 
//		{
//			for(int i=1;i<=n;i++)
//				cout<<rd(-1e8,1e8)<<" "<<rd(0,1e5)<<"\n";
//		}
//		if(G()&1)
		++k;
		if(k==3||k==4||nid==3||nid==4||nid==5)for(int i=2; i<=n; i++)cout<<i-1<<' ',cout<<i<<'\n';
		else if(k==1)for(int i=2;i<=n;i++)cout<<rd(1,i-1)<<' ',cout<<i<<'\n';
		else if(k==2)for(int i=2; i<=n; i++)cout<<1<<' ',cout<<i<<'\n';
		else {
//			cerr<<"$$\n";
			for(int i=1;i<=n;i++)fa[i]=i;
			for(int i=1; i<n; i++) {
				int x=rd(1,n),y=rd(1,n);
				while(find(x)==find(y))x=rd(1,n),y=rd(1,n);
//				cerr<<i<<"\n";
				cout<<x<<' ',cout<<y<<'\n',fa[find(y)]=find(x);
			}
			cerr<<"$$\n";
		}
//		for(int i=1;i<n;i++)cout<<i<<" "<<i+1<<"\n";
//		else 
//		{
//			for(int i=2;i<=n/2;i++)cout<<G()%(i-1)+1<<" "<<i<<"\n";
//			for(int i=n/2+1;i<=n;i++)cout<<i-1<<" "<<i<<"\n";
//		}
	}
	/*
	n=100000;
	cout<<n<<"\n";
	for(int i=1;i<=n;i++)cout<<(n-i)*1000-(int)1e8<<" "<<n-i<<"\n";
	for(int i=1;i<n;i++)cout<<i<<" "<<i+1<<"\n";
	n=100000;
	cout<<n<<"\n";
	for(int i=1;i<=n;i++)cout<<(n-i)*1000-(int)1e8<<" "<<n-i<<"\n";
	for(int i=1;i<n;i++)cout<<i<<" "<<i+1<<"\n";
	n=100000;
	cout<<n<<"\n";
	for(int i=1;i<=n;i++)cout<<(n-i)*1000-(int)1e8<<" "<<n-i<<"\n";
	for(int i=1;i<n;i++)cout<<i<<" "<<i+1<<"\n";
	n=100000;
	cout<<n<<"\n";
	for(int i=1;i<=n;i++)cout<<(n-i)*1000-(int)1e8<<" "<<n-i<<"\n";
	for(int i=1;i<n;i++)cout<<i<<" "<<i+1<<"\n";*/
	pc('1',1);
	return 0;
}
