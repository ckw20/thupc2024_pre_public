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
int main(){
	int no=io::F();
	char ss[222];
	sprintf(ss,"%d.in",no);
	freopen(ss,"w",stdout);
	int n=300,q=600,s=R(1,n);
	printf("%d %d %d\n",n,q,s);
	for(int i=2;i<=n;++i){
		int f;
		do{
			f=R(dmax(1,i-10),i-1);
		}
		while(deg[f]==2);
		deg[f]++;
		fa[i]=f;
		insert(f,i);
		printf("%d%c",f," \n"[i==n]);
	}
	dfs(1);
	for(int i=2;i<=n;++i){
		printf("%d%c",R(1,1000000000)," \n"[i==n]);
	}
	for(int i=2;i<=n;++i){
		printf("%d%c",R(1,1000000000)," \n"[i==n]);
	}
	int totp=0;
	while(q){
		int op=std::discrete_distribution<int>({10000.0*n,1.0*n,1.0*n,2.0*(n-totp),2.0*totp})(gen);
		if(op==0&&totp){
			int v;
			do{
				v=R(1,n);
			}
			while(occ[v]==0);
			std::vector<int> out;
			for(int p=e[v].next;p;p=e[p].next){
				if(!occ[e[p].to]&&e[p].to!=s){
					out.push_back(e[p].to);
				}
			}
			if(out.size()){
				int x=out[R(0,out.size()-1)];
				occ[x]=1;
				occ[v]=0;
			}
		}
		if(op==1&&s!=1&&!occ[fa[s]]){
			puts("1");
			--q;
			s=fa[s];
			while(R(0,10)&&s!=1&&!occ[fa[s]]){
				s=fa[s];
			}
		}
		if(op==2){
			std::vector<int> out;
			for(int p=e[s].next;p;p=e[p].next){
				if(e[p].to!=fa[s]&&!occ[e[p].to]){
					out.push_back(e[p].to);
				}
			}
			if(out.size()){
				puts("2");
				--q;
				s=out[R(0,out.size()-1)];
				while(R(0,10)){
					std::vector<int> out;
					for(int p=e[s].next;p;p=e[p].next){
						if(e[p].to!=fa[s]&&!occ[e[p].to]){
							out.push_back(e[p].to);
						}
					}
					if(out.size()){
						s=out[R(0,out.size()-1)];
					}
				}
			}
		}
		if(op==3&&s!=1&&!occ[1]){
			puts("3");
			--q;
			occ[1]=1;
			++totp;
		}
		if(op==4){
			std::vector<int> out;
			for(int i=1;i<=n;++i){
				if(occ[i]&&!(dfn[i]>dfn[s]&&dfn[i]<=cov[s])){
					out.push_back(i);
				}
			}
			if(out.size()){
				puts("4");
				--q;
				occ[out[R(0,out.size()-1)]]=0;
				--totp;
			}
		}
	}
	return 0;
}