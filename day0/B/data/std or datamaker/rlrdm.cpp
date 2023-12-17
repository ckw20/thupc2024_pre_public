#include<bits/stdc++.h>
#define ll long long 
#define dd double
#define LL __int128
#define ull unsigned ll
#define siz(A) ((int)A.size())
#define ll long long
using namespace std;
char gc(){static char buf[1<<16],*s,*t;if(s==t){t=(s=buf)+fread(buf,1,1<<16,stdin);if(s==t)return EOF;}return *s++;}
//#define getchar gc
int read()
{
	char c;
	int w=1;
	while((c=getchar())>'9'||c<'0')if(c=='-')w=-1;
	int ans=c-'0';
	while((c=getchar())>='0'&&c<='9')ans=(ans<<1)+(ans<<3)+c-'0';
	return ans*w;
}
void pc(char c,int op)
{
	static char buf[1<<16],*s=buf,*t=buf+(1<<16);
	(op||((*s++=c)&&s==t))&&(fwrite(buf,1,s-buf,stdout),s=buf);
}
void wt(ll x)
{
	if(x>9)wt(x/10);
	pc('0'+x%10,0);
}
void wts(ll x,char c)
{
	if(x<0)pc('-',0),x=-x;
	wt(x),pc(c,0);
}
/*以下写一个较为完备的生成数据的东西 */
//默认是windows环境 
random_device R;
mt19937 ABC(R());
//ll rd32(){return (rand()|(rand()<<15));}//到1e9 
//ll rd64(){return rd32()|(rd32()<<30);}//到1e18 
//ll rd(ll l,ll r){return l+rd64()%(r-l+1);}
#define rd32() (rd(0,1e9))
#define rd64() (rd(0,1e18))
ll rd(ll l,ll r){return uniform_int_distribution<ll>(l,r)(ABC);}
int n,m,q;
struct nod{int x,y,z;};
vector<nod>v;
const int xx=3e6+5;//默认1e6 
int id[xx];
void remark()
{
	for(int i=1;i<=n;i++)id[i]=i;
	random_shuffle(id+1,id+n+1);
}
void on()
{
	for(int i=0;i<v.size();i++)
	{
		v[i].x=id[v[i].x];
		v[i].y=id[v[i].y];
	}
}
void rdm_tree(){for(int i=2;i<=n;i++)v.push_back((nod){rd32()%(i-1)+1,i,0});}
void rerand(){random_shuffle(v.begin(),v.end());}
void reswap(){for(int i=0;i<v.size();i++)if(rand()&1)swap(v[i].x,v[i].y);}
void fstout(int op)
{
	//op=0表示不带权值 
	for(auto it:v)
	{
		wts(it.x,' ');
		wts(it.y,' ');
		if(op)wts(it.z,'\n');
		else pc('\n',0);
	}
}
void fullqz(ll L,ll R){for(int i=0;i<v.size();i++)v[i].z=rd(L,R);}
namespace pf
{
	int f[xx],p[xx];//父亲和prufer 
	int Rd[xx];
	void prufer()
	{
		for(int i=1;i<=n-2;i++)p[i]=rd32()%n+1;
		for(int i=1;i<n-1;i++)Rd[p[i]]++;p[n-1]=n;
		int j=1;
		for(int i=1;i<=n-1;i++,j++)
		{
			while(Rd[j])j++;f[j]=p[i];
			while(!(--Rd[p[i]])&&p[i]<j&&i<=n-1)f[p[i]]=p[i+1],i++;
		}
		for(int i=1;i<n;i++)v.push_back((nod){f[i],i,0});//注意prufer是以n为根的 
	}
}using pf::prufer;
struct node{int next,to,v;}e[xx<<1];
int cnt,h[xx];
void add(int x,int y,int z)
{
	cnt++;
	e[cnt].next=h[x];
	h[x]=cnt;
	e[cnt].to=y;
	e[cnt].v=z;
}
void bd(int op)//0表示有向 
{
	for(auto it:v)
	{
		add(it.x,it.y,it.z);
		if(op)add(it.y,it.x,it.z);
	}
}
//不保证无重边，保证无自环 
void fill()
{
	while(v.size()<m)
	{
		int x=rd32()%n+1,y=rd32()%n+1;
		if(x==y)continue;
		v.push_back({x,y,0});
	}
}
void fill2()//可以带自环 
{
	while(v.size()<m)
	{
		int x=rd32()%n+1,y=rd32()%n+1;
		v.push_back({x,y,0});
	}
}
ll a[xx];
void r_seq(ll L,ll R){for(int i=1;i<=n;i++)a[i]=rd(L,R);}
void outseq(){for(int i=1;i<=n;i++)wts(a[i],' ');pc('\n',0);}
map<pair<int,int> ,int>mp;
void cls(int op)//0表示也不存在反向边，1表示存在 
{
	vector<nod>w;
	mp.clear();
	for(auto it:v)
	{
		if(!op&&it.x>it.y)swap(it.x,it.y);
		if(mp[make_pair(it.x,it.y)])continue;
		mp[make_pair(it.x,it.y)]=1;
		w.push_back(it);
	}
	swap(w,v);
	while(v.size()<m)
	{
		int x=rd32()%n+1,y=rd32()%n+1;
		if(x==y)continue;
		if(x>y)swap(x,y);
		if(mp[make_pair(x,y)])continue;
		mp[make_pair(x,y)]=1;
		v.push_back({x,y,0});
	}
	return ;
}
void connected_map(int N,int M)//无重边/自环 
{
	n=N,m=M;
	prufer();
	fill();
	cls(0);
	remark();
	on();
	rerand();
}
void out()
{
	for(auto it:v)cout<<it.x<<" "<<it.y<<" "<<it.z<<"\n";
}
namespace ssc
{
	#define is(l,r) l<=testid&&testid<=r
	const int xx=1e6+5;
	int n,q;
	void one(int lim)
	{
		int nw=0;
		for(int i=1;i<=n;i++)
		{
			if(!rd(0,lim))nw=rd(0,2);
			cout<<nw<<" ";
		}
		puts("");
	}
	int a[xx];
	void two(int lim)
	{
		int nw=0;
		for(int i=1;i<=n;i++)
		{
			if(!rd(0,lim))nw=rd(0,1);
			a[i]=nw;
//			cout<<nw<<" ";
		}
		for(int i=1;i<=17;i++)a[rd(1,n)]=2;
		for(int i=1;i<=n;i++)cout<<a[i]<<" ";
		puts("");
	}
	void solve()
	{
		freopen("now.in","r",stdin);
		int testid=read(),op=0,q=5e5;
		n=5e5-rd(1,10);
		int k=rd(0,2)==0?rd(0,1000):rd(0,1)?rd(1,n/2):rd(n/2,n);
		cout<<n<<" "<<k<<"\n";
//		for(int i=2;i<=n/2;i++)cout<<i/2<<" "<<i<<"\n";
		for(int i=2;i<=n;i++)cout<<rd(max(i-1,1),i-1)<<" "<<i<<"\n";
		puts("");
		
		
//		if(is(1,4))n=20-rd(0,1);
//		if(is(5,8))n=500-rd(0,1);
//		if(is(9,12))n=5000-rd(0,3);
//		if(is(13,13))
//		{
//			n=5e5-rd(0,5);
//			cout<<n<<"\n";
//			for(int i=1;i<=n;i++)if(i==1||i==n)cout<<"0 ";else cout<<1000000000<<" ";
//			puts("");return;
//		}
//		if(is(14,15))
//		{
//			n=5e5-rd(0,5);
//			cout<<n<<"\n";
//			for(int i=1;i<=n;i++)if(i==1||i==n)cout<<"0 ";else if(i==2)cout<<rd(0,10)<<" ";else cout<<1000000000<<" ";
//			puts("");return;
//		}
//		if(is(16,20))n=5e5-rd(0,5);
//		for(int i=1;i<=n;i++)if(i==1||i==n)a[i]=0;else a[i]=rd(0,5);
//		if(n>20)
//		{
//			int T=n/500;
//			while(T--)
//				a[rd(2,n-1)]=rd(0,1000000000);
//			T=n/100;
//			while(T--)
//				a[rd(2,n-1)]=rd(0,n);
//		}
//		cout<<n<<'\n';
//		for(int i=1;i<=n;i++)cout<<a[i]<<" ";
//		puts("");
	}
}
signed main(){
	freopen("seed.in","r",stdin);
	int ooo=read();
	srand(ooo);
	freopen("tree.in","w",stdout);
	ssc::solve();
	
	pc('1',1);
	freopen("seed.in","w",stdout);
	cout<<ooo+777<<"\n";
	return 0;
}
//#include<bits/stdc++.h>
//#define ll long long
//using namespace std;
//char gc(){static char buf[1<<16],*s,*t;if(s==t){t=(s=buf)+fread(buf,1,1<<16,stdin);if(s==t)return EOF;}return *s++;}
////#define getchar gc
//int read()
//{
//	char c;
//	int w=1;
//	while((c=getchar())>'9'||c<'0')if(c=='-')w=-1;
//	int ans=c-'0';
//	while((c=getchar())>='0'&&c<='9')ans=(ans<<1)+(ans<<3)+c-'0';
//	return ans*w;
//}
//void pc(char c,int op)
//{
//	static char buf[1<<16],*s=buf,*t=buf+(1<<16);
//	(op||((*s++=c)&&s==t))&&(fwrite(buf,1,s-buf,stdout),s=buf);
//}
//void wt(ll x)
//{
//	if(x>9)wt(x/10);
//	pc('0'+x%10,0);
//}
//void wts(ll x,char c)
//{
//	if(x<0)pc('-',0),x=-x;
//	wt(x),pc(c,0);
//}
///*以下写一个较为完备的生成数据的东西 */
////默认是windows环境 
//random_device R;
//mt19937 ABC(R());
////ll rd32(){return (rand()|(rand()<<15));}//到1e9 
////ll rd64(){return rd32()|(rd32()<<30);}//到1e18 
////ll rd(ll l,ll r){return l+rd64()%(r-l+1);}
//#define rd32() (rd(0,1e9))
//#define rd64() (rd(0,1e18))
//ll rd(ll l,ll r){return uniform_int_distribution<ll>(l,r)(ABC);}
//int n,m,q;
//struct nod{int x,y,z;};
//vector<nod>v;
//const int xx=3e6+5;//默认1e6 
//int id[xx];
//void remark()
//{
//	for(int i=1;i<=n;i++)id[i]=i;
//	random_shuffle(id+1,id+n+1);
//}
//void on()
//{
//	for(int i=0;i<v.size();i++)
//	{
//		v[i].x=id[v[i].x];
//		v[i].y=id[v[i].y];
//	}
//}
//void rdm_tree(){for(int i=2;i<=n;i++)v.push_back((nod){rd32()%(i-1)+1,i,0});}
//void rerand(){random_shuffle(v.begin(),v.end());}
//void reswap(){for(int i=0;i<v.size();i++)if(rand()&1)swap(v[i].x,v[i].y);}
//void fstout(int op)
//{
//	//op=0表示不带权值 
//	for(auto it:v)
//	{
//		wts(it.x,' ');
//		wts(it.y,' ');
//		if(op)wts(it.z,'\n');
//		else pc('\n',0);
//	}
//}
//void fullqz(ll L,ll R){for(int i=0;i<v.size();i++)v[i].z=rd(L,R);}
//namespace pf
//{
//	int f[xx],p[xx];//父亲和prufer 
//	int Rd[xx];
//	void prufer()
//	{
//		for(int i=1;i<=n-2;i++)p[i]=rd32()%n+1;
//		for(int i=1;i<n-1;i++)Rd[p[i]]++;p[n-1]=n;
//		int j=1;
//		for(int i=1;i<=n-1;i++,j++)
//		{
//			while(Rd[j])j++;f[j]=p[i];
//			while(!(--Rd[p[i]])&&p[i]<j&&i<=n-1)f[p[i]]=p[i+1],i++;
//		}
//		for(int i=1;i<n;i++)v.push_back((nod){f[i],i,0});//注意prufer是以n为根的 
//	}
//}using pf::prufer;
//struct node{int next,to,v;}e[xx<<1];
//int cnt,h[xx];
//void add(int x,int y,int z)
//{
//	cnt++;
//	e[cnt].next=h[x];
//	h[x]=cnt;
//	e[cnt].to=y;
//	e[cnt].v=z;
//}
//void bd(int op)//0表示有向 
//{
//	for(auto it:v)
//	{
//		add(it.x,it.y,it.z);
//		if(op)add(it.y,it.x,it.z);
//	}
//}
////不保证无重边，保证无自环 
//void fill()
//{
//	while(v.size()<m)
//	{
//		int x=rd32()%n+1,y=rd32()%n+1;
//		if(x==y)continue;
//		v.push_back({x,y,0});
//	}
//}
//void fill2()//可以带自环 
//{
//	while(v.size()<m)
//	{
//		int x=rd32()%n+1,y=rd32()%n+1;
//		v.push_back({x,y,0});
//	}
//}
//ll a[xx];
//void r_seq(ll L,ll R){for(int i=1;i<=n;i++)a[i]=rd(L,R);}
//void outseq(){for(int i=1;i<=n;i++)wts(a[i],' ');pc('\n',0);}
//map<pair<int,int> ,int>mp;
//void cls(int op)//0表示也不存在反向边，1表示存在 
//{
//	vector<nod>w;
//	mp.clear();
//	for(auto it:v)
//	{
//		if(!op&&it.x>it.y)swap(it.x,it.y);
//		if(mp[make_pair(it.x,it.y)])continue;
//		mp[make_pair(it.x,it.y)]=1;
//		w.push_back(it);
//	}
//	swap(w,v);
//	while(v.size()<m)
//	{
//		int x=rd32()%n+1,y=rd32()%n+1;
//		if(x==y)continue;
//		if(x>y)swap(x,y);
//		if(mp[make_pair(x,y)])continue;
//		mp[make_pair(x,y)]=1;
//		v.push_back({x,y,0});
//	}
//	return ;
//}
//void connected_map(int N,int M)//无重边/自环 
//{
//	n=N,m=M;
//	prufer();
//	fill();
//	cls(0);
//	remark();
//	on();
//	rerand();
//}
//void out()
//{
//	for(auto it:v)cout<<it.x<<" "<<it.y<<" "<<it.z<<"\n";
//}
//namespace ssc
//{
//	#define is(l,r) l<=testid&&testid<=r
//	int p[]={1,2,4,6,12,24,36,48,60,120,180,240,360,720,840,1260,1680,2520,5040,7560,10080,15120,20160,25200,27720,45360,50400,55440,83160,110880,166320,221760,277200,332640,498960,554400,665280,720720,1081080,1441440,2162160,2882880,3603600,4324320,6486480,7207200,8648640,10810800,14414400,17297280,21621600,32432400,36756720,43243200,61261200,73513440,110270160,122522400,147026880,183783600,245044800,294053760,367567200,551350800,698377680,735134400,1102701600,1396755360,2001000000};
//	int prim[xx],mn[xx],Cnt;
//	void pre(int n)
//	{
//		for(int i=2;i<=n;i++)
//		{
//			if(!mn[i])mn[i]=i,prim[++Cnt]=i;
//			for(int j=1;j<=Cnt;j++)
//			{
//				if(prim[j]*i>n)break;
//				mn[i*prim[j]]=prim[j];
//				if(i%prim[j]==0)break;
//			}
//		}
//	}
//	int yz[xx],yct[xx],tt,im[xx],nt,n;
//	void gyz(int x)
//	{
//		tt=0,yz[++tt]=1;
//		while(x!=1)
//		{
//			int M=mn[x],ct=0,ntt=tt;
//			while(x%M==0)++ct,x/=M;
//			for(int i=1,ty=1;(ty*=M),i<=ct;i++)
//				for(int j=1;j<=ntt;j++)
//					yz[++tt]=yz[j]*ty;
//		}
//	}
//	struct pr{int x,y;};
//	vector<pr>ans;
//	vector<vector<pr>>all;
//	void solve()
//	{
//		freopen("now.in","r",stdin);
//		pre(xx-1);
//		int testid=read(),nlim=3e6,mlim,slim=3e6;
//		if(is(1,4))
//			nlim=20;
//		if(is(5,8))
//			nlim=5000,slim=5000;
//		if(is(9,12))
//			slim=5000;
//		if(is(13,20));
//		if(nlim>1e6&&slim==3e6)
//		{
//			int id=2882880;
//			ans.clear();
//			int num=1e6+(rd(1,5000));
//			while(num--)ans.push_back({id-1,rd(0,1)});
//			int ty=rd(1,100000);
//			while(ty--)ans.push_back({rd(1,slim),rd(0,1)});
//			gyz(id);
//			ty=rd(1,100000);
//			while(ty--)ans.push_back({max(1,yz[rd(1,tt)]-(int)rd(0,1)),rd(0,1)});
//			all.push_back(ans);
//			nlim-=ans.size();
//		}
//		if(nlim>5e5)
//		{
//			nlim-=5e5;
//			int re=5e5;
//			while(re>100&&all.size()<10000)
//			{
//				ans.clear();
//				int n=rd(10,min(re,100));
//				int nn=n;
//				re-=n;
//				int r=min(n,3);
//				n-=r;
//				while(r--)ans.push_back({rd(1,3e6),!(rd(0,5)<3)});
//				while(n)
//				{
//					int rm=rd(1,min(n,600));
//					n-=rm;
//					int t=0;
//					while(p[t+1]<=slim)++t;
//					int nw=p[rd(0,t)]-1;
//					if(rd(0,4)==0)nw=rd(1,3e6);
//					nw=max(nw,1);
//					ans.push_back({nw,(rd(0,1))});
//					--rm;
//					gyz(nw+1);
//					while(rm--)
//					{
//						int op=max(1,yz[rd(1,tt)]-(int)rd(0,1));
//						if(op==1&&rd(0,10))
//						{
//							++rm;
//							continue;
//						}
//						ans.push_back({op,!(rd(0,4)<3)});
//					}
//	//					ans.push_back({,});
//				}
//				all.push_back(ans);
////				cerr<<nn<<" "<<ans.size()<<" "<<nlim<<" "<<all.size()<<"@\n";
//			}
//		}
//		
//		else 
//		if(nlim>2000)
//		{
//			nlim-=2000;
//			int re=2000;
//			while(re>20&&all.size()<10000)
//			{
//				ans.clear();
//				int n=rd(10,min(re,40));
//				int nn=n;
//				re-=n;
//				int r=min(n,3);
//				n-=r;
//				while(r--)ans.push_back({rd(1,3e6),!(rd(0,5)<3)});
//				while(n)
//				{
//					int rm=rd(1,min(n,600));
//					n-=rm;
//					int t=0;
//					while(p[t+1]<=slim)++t;
//					int nw=p[rd(0,t)]-1;
//					if(rd(0,4)==0)nw=rd(1,3e6);
//					nw=max(nw,1);
//					ans.push_back({nw,(rd(0,1))});
//					--rm;
//					gyz(nw+1);
//					while(rm--)
//					{
//						int op=max(1,yz[rd(1,tt)]-(int)rd(0,1));
//						if(op==1&&rd(0,10))
//						{
//							++rm;
//							continue;
//						}
//						ans.push_back({op,!(rd(0,4)<3)});
//					}
//	//					ans.push_back({,});
//				}
//				all.push_back(ans);
////				cerr<<nn<<" "<<ans.size()<<" "<<nlim<<" "<<all.size()<<"@\n";
//			}
//		}
//		while(nlim>0&&all.size()<10000)
//		{
//			ans.clear();
//			int n=rd(1,nlim);
//			int nn=n;
//			nlim-=n;
//			int r=min(n,3);
//			n-=r;
//			while(r--)ans.push_back({rd(1,5000),!(rd(0,5)<3)});
////			cerr<<"!!!\n";
//			while(n)
//			{
//				int rm=rd(1,min(n,600));
//				n-=rm;
//				int t=0;
//				while(p[t+1]<=slim)++t;
//				int nw=p[rd(0,t)]-1;
//				if(rd(0,4)==0)nw=rd(1,3e6);
//				nw=max(nw,1);
//				ans.push_back({nw,(rd(0,1))});
//				--rm;
//				gyz(nw+1);
//				while(rm--)
//				{
//					int op=max(1,yz[rd(1,tt)]-(int)rd(0,1));
//					if(op==1&&rd(0,10))
//					{
//						++rm;
//						continue;
//					}
//					ans.push_back({op,!(rd(0,4)<3)});
//				}
////					ans.push_back({,});
//			}
//			all.push_back(ans);
////			cerr<<nn<<" "<<ans.size()<<" "<<nlim<<"@\n";
//		}
//		shuffle(all.begin(),all.end(),ABC);
//		cout<<all.size()<<"\n";
//		for(auto it:all)
//		{
//			shuffle(it.begin(),it.end(),ABC);
//			cout<<it.size()<<"\n";
//			for(auto It:it)cout<<It.x<<" ";
//			puts("");
//			
//			for(auto It:it)cout<<It.y<<" ";
//			puts("");
//		}
//	}
//}
//signed main(){
//	freopen("seed.in","r",stdin);
//	int ooo=read();
//	srand(ooo);
//	freopen("number.in","w",stdout);
//	ssc::solve();
//	
//	pc('1',1);
//	freopen("seed.in","w",stdout);
//	cout<<ooo+777<<"\n";
//	return 0;
//}
