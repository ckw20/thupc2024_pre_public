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
//2e6 125357
//2^{17}=131072
// 0~16 。 
//980000 
//65345 
//哎，艹了 
const int xx=1e6+5;
int n,sum[xx],a[xx],b[xx],pos[xx];
int lb(int x){return x&-x;}
void add(int x,int y){for(;x<xx;x+=lb(x))sum[x]+=y;}
int ask(int x){int ans=0;for(;x;x-=lb(x))ans+=sum[x];return ans;}
int kth(int k)
{
	int S=0,id=0;
	for(int i=20;i>=0;i--)
		if(id+(1<<i)<xx&&S+sum[id+(1<<i)]<k)id+=(1<<i),S+=sum[id];
	assert(id+1<=n);
	return id+1;
}
const int D=19;
int ct;
struct st
{
	priority_queue<int,vector<int>,greater<int> >A,B;
	int size(){return siz(A)-siz(B);}
	void clear(){while(siz(A)&&siz(B)&&A.top()==B.top())A.pop(),B.pop();}
	int top()
	{
		assert(size()),clear();
		return A.top();
	}
	void ins(int x){++ct,A.push(x);}
	void era(int x){B.push(x);}
}s[(1<<(D+1))+10];
int len;
void get(int x,int op)
{
	if(b[x]==0)return;
	int cur=0;
	for(int i=0;i<=D;i++)
	{
		if(x+i<=len)
		{
			cur<<=1,cur|=b[x+i];
//			assert(cur<=(1<<(D+1))+10);
			if(op==1)s[cur].ins(pos[x]);
			else s[cur].era(pos[x]);
		}
		else break;
	}
}
//下标应该存绝对下标。 
char ED;
int main(){
	cerr<<abs(&ST-&ED)/1024.0/1024<<"\n";
//	freopen("a.in","r",stdin);
//	freopen("binary.in","r",stdin);
//	freopen("binary.out","w",stdout);
	n=len=read();
	for(int i=1;i<=n;i++)
	{
		char c;
		while((c=getchar())!='0'&&c!='1');
		a[i]=c-'0';
	}
	for(int i=1;i<=n;i++)b[i]=a[i];
	for(int i=1;i<=n;i++)add(i,1),pos[i]=i;
	for(int i=1;i<=n;i++)get(i,1);
//	return 0;
	
	for(int i=1;i<=n;i++)
	{
//		if(i>(1<<(D+1)))
//		{
//			puts("-1 0");
//			continue;
//		}
		if(!siz(s[i]))
		{
			puts("-1 0");
			continue;
		}
		int A=ask(s[i].top()),tl=__lg(i)+1,L=max(1,A-D),R=min(A+tl-1+D,len);
		cout<<A<<" "<<siz(s[i])<<"\n";
		for(int j=L;j<=R;j++)pos[j]=kth(j),b[j]=a[pos[j]];
		for(int j=L;j<=A+tl-1;j++)get(j,-1);
		for(int j=A;j<=A+tl-1;j++)add(pos[j],-1);
		len-=tl;
		for(int j=A+tl;j<=R;j++)b[j-tl]=b[j];
		for(int j=L;j<A;j++)get(j,1);
//		if(i%10000==0)cerr<<ct<<"#\n";
	}
//	int res=0;
//	for(int i=1;i;i++)
//	{
//		res+=(__lg(i)+1);
//		if(res>980000)
//		{
//			cout<<i<<"#\n";
//			exit(0);
//		}
//	}
//	
	pc('1',1);
	return 0;
}


}signed main(){return ifzw::main();}
