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
const int xx=5e5+5;
struct seg
{
	int len,tag;
	ll sum;
	int L[3],R[3];
	int lm[3],rm[3];
}t[xx<<2];
#define cs(A,B) rotate(A,A+B,A+3)
const int M=3;
int n,q,a[xx];
// lm 前缀 rm 后缀 
void ad(int k,int z)
{
	z%=M;
	if(z)
	{
		(t[k].tag+=z)%=M;
		cs(t[k].L,3-z),cs(t[k].R,3-z);
		cs(t[k].lm,3-z),cs(t[k].rm,3-z);
	}
}
void pd(int k){if(t[k].tag)ad(k<<1,t[k].tag),ad(k<<1|1,t[k].tag),t[k].tag=0;}
ll get(int len){return 1ll*len*(len+1)/2;}
void upd(seg&A,seg&B,seg&C)
{
	C.sum=A.sum+B.sum;
	for(int i=0;i<3;i++)
	{
		C.sum-=get(A.rm[i]),C.sum-=get(B.lm[i]),C.sum+=get(A.rm[i]+B.lm[i]);
		C.lm[i]=A.lm[i]==A.len?A.lm[i]+B.lm[i]:A.lm[i];
		C.rm[i]=B.rm[i]==B.len?B.rm[i]+A.rm[i]:B.rm[i];
		if(!A.L[i]||!B.L[i])C.L[i]=A.L[i]+B.L[i],C.R[i]=A.R[i]+B.R[i];
		else C.sum-=get(B.L[i]-A.R[i]-1),C.L[i]=A.L[i],C.R[i]=B.R[i];
	}
}
//同色段加，异色  减。 
void cg(int k,int l,int r,int x,int y)
{
	if(x<=l&&r<=y)return ad(k,1);
	pd(k);int mid=l+r>>1;
	if(x<=mid)cg(k<<1,l,mid,x,y);
	if(mid<y)cg(k<<1|1,mid+1,r,x,y);
	upd(t[k<<1],t[k<<1|1],t[k]);
}
void build(int k,int l,int r)
{
	t[k].len=r-l+1;
	if(l==r)return t[k].L[a[l]]=t[k].R[a[l]]=l,t[k].sum=1,t[k].lm[a[l]]=t[k].rm[a[l]]=1,void();
	int mid=l+r>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	upd(t[k<<1],t[k<<1|1],t[k]);
}
void run()
{
	ll ans=get(n);
	ans+=t[1].sum;
	for(int i=0;i<3;i++)
	{
		if(!t[1].L[i])ans-=get(n);
		else ans-=get(t[1].L[i]-1),ans-=get(n-t[1].R[i]);
	}
	cout<<ans<<"\n";
}
char ED;
int main(){
	cerr<<abs(&ST-&ED)/1024.0/1024<<"\n";
	freopen("maintaining.in","r",stdin);
	freopen("maintaining.out","w",stdout);
	n=read(),q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	build(1,1,n),run();
	while(q--)
	{
		int l=read(),r=read();
		cg(1,1,n,l,r),run();
	}
	pc('1',1);
	return 0;
}

