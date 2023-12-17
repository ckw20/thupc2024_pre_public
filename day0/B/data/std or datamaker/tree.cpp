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
//共用 point 系统 
struct pt
{
	int l,r,dst,siz;
	ll v,tg;
}t[xx];
void ad(int k,ll v){if(k)t[k].tg+=v,t[k].v+=v;}
void pd(int k){if(t[k].tg)ad(t[k].l,t[k].tg),ad(t[k].r,t[k].tg),t[k].tg=0;}
void upd(int k){t[k].siz=t[t[k].l].siz+t[t[k].r].siz+1;}

int m1(int x,int y)//大根 
{
//	cerr<<x<<" "<<y<<"@\n";
	if(!x||!y)return x+y;
	pd(x),pd(y);
	if(t[x].v<t[y].v)swap(x,y);
	t[x].r=m1(t[x].r,y);
	if(t[t[x].r].dst>t[t[x].l].dst)swap(t[x].l,t[x].r);
	t[x].dst=t[t[x].r].dst+1;
	return upd(x),x;
}
int m2(int x,int y)//小根 
{
//	cerr<<x<<" "<<y<<"^&^&\n";
	if(!x||!y)return x+y;
	assert(x!=y);
	pd(x),pd(y);
	if(t[x].v>t[y].v)swap(x,y);
	t[x].r=m2(t[x].r,y);
	if(t[t[x].r].dst>t[t[x].l].dst)swap(t[x].l,t[x].r);
	t[x].dst=t[t[x].r].dst+1;
	return upd(x),x;
}
//就加入的点叫做 x 
int tl[xx],tr[xx],A;

void print(int x)
{
	if(!x)return ;
	pd(x);
	cout<<t[x].v<<" ";
	print(t[x].l),print(t[x].r);
}
void pr(int x)
{
	print(tl[x]),print(tr[x]);
	puts("");
}
void dfs(int x,int y)
{
//		cerr<<"A B"<<"#\n";
	t[x].siz=1;
	for(int i=h[x];i;i=e[i].next)
	{
		if(e[i].to==y)continue;
		dfs(e[i].to,x);
//		cerr<<t[tl[e[i].to]].siz<<" "<<t[tl[x]].siz<<"##\n";
		tl[x]=m1(tl[x],tl[e[i].to]);
//		cerr<<t[tl[e[i].to]].siz<<" "<<t[tl[x]].siz<<"QQ\n";
		tr[x]=m2(tr[x],tr[e[i].to]);
	}
	
	t[x].v=0,t[x].tg=0;
	if(t[tl[x]].v>=0)tl[x]=m1(tl[x],x);
	else tr[x]=m2(tr[x],x);
//	cerr<<x<<" "<<t[tl[x]].siz<<" "<<t[tr[x]].siz<<"$AAAAAAAAAAA1%\n";
	while(t[tl[x]].siz<A&&t[tr[x]].siz)
	{
//		cerr<<"A B"<<"#\n";
//	cerr<<x<<" "<<y<<"@\n";
//		cerr<<t[tr[x]].siz<<" "<<t[tl[x]].siz<<" "<<A<<" "<<tl[x]<<" "<<tr[x]<<" #\n";
//		cerr<<t[tl[x]].siz<<"@#23\n";
		y=tr[x],pd(y);
		tr[x]=m2(t[tr[x]].l,t[tr[x]].r);
		t[y].siz=1,t[y].l=t[y].r=0,t[y].dst=0;
		tl[x]=m1(tl[x],y);
//		cerr<<t[tr[x]].siz<<" "<<t[tl[x]].siz<<" "<<A<<" #\n";
	}
//	cerr<<x<<" "<<t[tl[x]].siz<<" "<<t[tr[x]].siz<<"$BBBBBBBBBB1%\n";
	while(t[tl[x]].siz>A)
	{
//		cerr<<"A B"<<"#\n";
//		cerr<<t[tl[x]].siz<<"@#ab\n";
		y=tl[x],pd(y);
		tl[x]=m1(t[tl[x]].l,t[tl[x]].r);
		t[y].siz=1,t[y].l=t[y].r=0,t[y].dst=0;
		tr[x]=m2(tr[x],y);
	}
	if(x!=1)
	{
		if(tk&1)
		{
			ad(tl[x],-2);
			y=tr[x],pd(y);
			tr[x]=m2(t[tr[x]].l,t[tr[x]].r);
			if(y)t[y].siz=1,t[y].l=t[y].r=0,t[y].dst=0;
			ad(tr[x],2),tr[x]=m2(tr[x],y);
		}
		else ad(tl[x],-2),ad(tr[x],2);
	}
//	cerr<<x<<" "<<t[tl[x]].siz<<" "<<t[tr[x]].siz<<"$!!!!!!!!!!!!!!!!!1%\n";
//	cerr<<x<<"@@!!SS\n";
//	pr(x);
	
}
char ED;
int main(){
	t[0].dst=-1;
	cerr<<abs(&ST-&ED)/1024.0/1024<<"\n";
	freopen("a.in","r",stdin);
//	freopen("a.out","w",stdout);
//	freopen("tree.in","r",stdin);
//	freopen("tree.out","w",stdout);
	n=read(),tk=read(),A=tk/2;
	for(int i=1;i<n;i++)
	{
		int x=read(),y=read();
		add(x,y),add(y,x);
	}
	if(!tk)
	{
		puts("0");
		return 0;
	}
	dfs(1,0);
//	for(int i=1;i<=n;i++)cout<<t[i].l<<" "<<t[i].r<<"SS\n";
//	cerr<<tl[1]<<" "<<tr[1]<<" "<<t[tl[1]].siz<<" "<<t[tr[1]].siz<<"%%\n";
//	exit(0);
//	cerr<<"!\n";
	vector<ll>cf;
	while(t[tl[1]].siz)
	{
//		cerr<<tl[1]<<" "<<t[tl[1]].siz<<" "<<t[tl[1]].l<<" "<<t[tl[1]].r<<"@#2\n";
		cf.push_back(t[tl[1]].v);pd(tl[1]);
		tl[1]=m1(t[tl[1]].l,t[tl[1]].r);
	}
//	exit(0);
	while(t[tr[1]].siz)
	{
//		cerr<<tr[1]<<"%^%^\n";
		cf.push_back(t[tr[1]].v);pd(tr[1]);
		tr[1]=m2(t[tr[1]].l,t[tr[1]].r);
	}
	sort(cf.begin(),cf.end());
	ll ini=1ll*(n-1)*tk;
//	cerr<<siz(cf)<<"$%$%%%\n";
//	cerr<<siz(cf)<<" "<<tk<<"%$%\n";
	assert(siz(cf)>=tk);
	for(int i=0;i<tk;i++)ini+=cf[i];
//	for(int i=0;i<tk;i++)cerr<<i<<" "<<cf[i]<<"$\n";
//	cerr<<cf[0]<<"$\n";
	cout<<ini<<"\n";
	pc('1',1);
	return 0;
}


}signed main(){return ifzw::main();}
