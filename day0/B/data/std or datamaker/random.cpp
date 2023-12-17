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
//	freopen("now.in","r",stdin);
	int op=rd(0,1)?10:1000;
	int n=rd(1,op),k=rd(1,n);
	cout<<n<<" "<<k<<"\n";
	for(int i=2;i<=n;i++)cout<<rd(1,i-1)<<" "<<i<<"\n";
	pc('1',1);
	return 0;
}
