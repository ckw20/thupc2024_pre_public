#include<bits/stdc++.h>
#define cmin(a,b) (a>(b)?a=(b),1:0)
#define cmax(a,b) (a<(b)?a=(b),1:0)
#define dmin(a,b) ((a)<(b)?(a):(b))
#define dmax(a,b) ((a)>(b)?(a):(b))
namespace io{
	int F(){
		int n=0,F=0;
		char ch;
		while((ch=getchar())!='-'&&(ch<'0'||ch>'9'));
		ch=='-'?F=1:n=ch-'0';
		while((ch=getchar())>='0'&&ch<='9')n=n*10+ch-'0';
		return F?-n:n;
	}
	long long G(){
		long long n=0,F=0;
		char ch;
		while((ch=getchar())!='-'&&(ch<'0'||ch>'9'));
		ch=='-'?F=1:n=ch-'0';
		while((ch=getchar())>='0'&&ch<='9')n=n*10+ch-'0';
		return F?-n:n;
	}
}
std::random_device dev;
std::mt19937_64 gen(dev());
int R(int l,int r){
	return std::uniform_int_distribution<int>(l,r)(gen);
}
int deg[333],fa[333];
struct edge{
	int to;
	int next;
}e[999];
int pe=333;
void insert(int a,int to){
	e[pe]=(edge){to,e[a].next};
	e[a].next=pe++;
}
int dfn[333],cov[333],dfc;
void dfs(int o){
	dfn[o]=++dfc;
	for(int p=e[o].next;p;p=e[p].next){
		if(e[p].to!=fa[o])
			dfs(e[p].to);
	}
	cov[o]=dfc;
}
int occ[333];
int p[333],r[333];
int main(){
	int no=22;
	char ss[222];
	sprintf(ss,"%d.in",no);
	freopen(ss,"w",stdout);
	int n=301,q=600,s=150;
	printf("%d %d %d\n",n,q,s);
	for(int i=2;i<=n;++i){
		int f=i/2*2-1;
		deg[f]++;
		fa[i]=f;
		insert(f,i);
		insert(i,f);
		printf("%d%c",f," \n"[i==n]);
	}
	dfs(1);
	for(int i=2;i<=301;++i){
		p[i]=i*i*i;
	}
	r[149]=1e9-123;
	r[150]=1e9-1;
	for(int i=2;i<=n;++i){
		printf("%d%c",r[i]," \n"[i==n]);
	}
	for(int i=2;i<=n;++i){
		printf("%d%c",p[i]," \n"[i==n]);
	}
	int totp=0;
	for(int i=1;i<=155;++i){
		puts("3");
	}
	for(int i=1;i<=144;++i){
		puts("1");
		puts("2");
	}
	puts("1");
	for(int i=1;i<=55;++i){
		puts("4");
	}
	puts("2");
	for(int i=1;i<=100;++i){
		puts("4");
	}
	return 0;
}