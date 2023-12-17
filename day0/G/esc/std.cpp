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
struct edge{
	int to;
	int next;
}e[999];
int pe=333;
void insert(int a,int to){
	e[pe]=(edge){to,e[a].next};
	e[a].next=pe++;
}
int q;
int fa[333],r[333],p[333],siz[333],lc[333],rc[333];
int op[666];
bool isrc[333];
int totp[666];
int _lc(int o){
	if(!e[o].next){
		return 0;
	}
	return e[e[o].next].to;
}
int _rc(int o){
	if(!e[o].next||!e[e[o].next].next){
		return 0;
	}
	return e[e[e[o].next].next].to;
}
int dfn[333],cov[333],dfc;
void dfs(int o){
	dfn[o]=++dfc;
	for(int p=e[o].next;p;p=e[p].next){
		dfs(e[p].to);
	}
	cov[o]=dfc;
}
long long in[333][333],out[333][333];
std::vector<std::vector<long long> > f[666][333][2],inc[666][333];
long long profit(int t,int o,int l,int r){
	return ::r[o]+in[lc[o]][l]+in[rc[o]][r]+out[o][totp[t]-l-r];
}
const long long INF=0x3f3f3f3f3f3f3f3fll;
long long INC(int,int,int,int);
long long F(int t,int o,int ok,int l,int r){
	if(t==q+1){
		return 0;
	}
	if(!(f[t][o][ok].size()>l&&f[t][o][ok][l].size()>r)){
		return -INF;
	}
	auto &ret=f[t][o][ok][l][r];
	if(ret!=-INF){
		return ret;
	}
	++ret;
	if(op[t]==3){
		if(totp[t]-l-r<=siz[1]-siz[o]){
			long long tmp=profit(t,o,l,r)+F(t+1,o,op[t+1]>2,l,r);
			cmax(ret,tmp);
		}
	}
	if(op[t]==4){
		if(totp[t]>=l+r){
			long long tmp=profit(t,o,l,r)+F(t+1,o,op[t+1]>2,l,r);
			cmax(ret,tmp);
		}
	}
	if(op[t]<=2){
		if(ok){
			long long tmp=profit(t,o,l,r)+F(t+1,o,op[t+1]>2,l,r);
			cmax(ret,tmp);
		}
	}
	if(op[t]==1){
		if(totp[t]-l-r<siz[1]-siz[o]){
			if(isrc[o]){
				long long tmp=INC(t,o,dmax(0,totp[t]-l-r-(siz[1]-siz[fa[o]])),l+r);
				cmax(ret,tmp);
			}
			else{
				long long tmp=INC(t,o,l+r,dmax(0,totp[t]-l-r-(siz[1]-siz[fa[o]])));
				cmax(ret,tmp);
			}
		}
	}
	if(op[t]==2){
		if(l<siz[lc[o]]){
			long long tmp=INC(t,lc[o],dmin(l,siz[lc[lc[o]]]),l-dmin(l,siz[lc[lc[o]]]));
			cmax(ret,tmp);
		}
		if(r<siz[rc[o]]){
			long long tmp=INC(t,rc[o],dmin(r,siz[lc[rc[o]]]),r-dmin(r,siz[lc[rc[o]]]));
			cmax(ret,tmp);
		}
	}
	return ret;
}
long long INC(int t,int o,int l,int r){
	if(inc[t][o].size()<=l||inc[t][o][l].size()<=r){
		return -INF;
	}
	if(inc[t][o][l][r]!=-INF){
		return inc[t][o][l][r];
	}
	++inc[t][o][l][r];
	if(op[t]==1){
		long long tmp=F(t,fa[o],1,l,r);
		cmax(inc[t][o][l][r],tmp);
		if(r+l<totp[t]&&(isrc[o]?l<siz[lc[fa[o]]]:r<siz[rc[fa[o]]])){
			tmp=isrc[o]?INC(t,o,l+1,r):INC(t,o,l,r+1);
			cmax(inc[t][o][l][r],tmp);
		}
	}
	if(op[t]==2){
		long long tmp=F(t,o,1,l,r);
		cmax(inc[t][o][l][r],tmp);
		if(l&&r<siz[rc[o]]){
			tmp=INC(t,o,l-1,r+1);
			cmax(inc[t][o][l][r],tmp);
		}
	}
	return inc[t][o][l][r];
}
int main(){
	int n=io::F(),q=io::F(),s=io::F();
	::q=q;
	for(int i=2;i<=n;++i){
		fa[i]=io::F();
		insert(fa[i],i);
	}
	dfs(1);
	for(int i=2;i<=n;++i){
		r[i]=io::F();
	}
	for(int i=2;i<=n;++i){
		p[i]=io::F();
	}
	for(int i=1;i<=q;++i){
		op[i]=io::F();
	}
	for(int i=1;i<=q;++i){
		totp[i]=totp[i-1]+(op[i]==3)-(op[i]==4);
		if(totp[i]<0||totp[i]>=n){
			puts("No solution.");
			return 0;
		}
	}
	for(int i=1;i<=n;++i){
		siz[i]=1;
	}
	for(int i=n;i>1;--i){
		siz[fa[i]]+=siz[i];
	}
	for(int i=1;i<=n;++i){
		lc[i]=_lc(i);
		rc[i]=_rc(i);
	}
	for(int i=1;i<=n;++i){
		if(rc[i]){
			isrc[rc[i]]=1;
		}
	}
	for(int i=1;i<=n;++i){
		std::vector<int> inp,outp;
		for(int j=1;j<=n;++j){
			if(dfn[j]>=dfn[i]&&dfn[j]<=cov[i]){
				inp.push_back(p[j]);
			}
			else{
				outp.push_back(p[j]);
			}
		}
		std::sort(inp.begin(),inp.end(),std::greater<int>());
		std::sort(outp.begin(),outp.end(),std::greater<int>());
		for(int j=0;j<inp.size();++j){
			in[i][j+1]=in[i][j]+inp[j];
		}
		for(int j=0;j<outp.size();++j){
			out[i][j+1]=out[i][j]+outp[j];
		}
	}
	for(int i=0;i<=q;++i){
		for(int o=1;o<=n;++o){
			for(int ok=1;ok>=(op[i]>2);--ok){
				f[i][o][ok].resize(dmin(siz[lc[o]],totp[i])+1,std::vector<long long>(dmin(siz[rc[o]],totp[i])+1,-0x3f3f3f3f3f3f3f3fll));
				if(op[i]==1&&o!=1)
					inc[i][o].resize(dmin(siz[lc[fa[o]]],totp[i])+1,std::vector<long long>(dmin(siz[rc[fa[o]]],totp[i])+1,-0x3f3f3f3f3f3f3f3fll));
				if(op[i]==2)
					inc[i][o].resize(dmin(siz[lc[o]],totp[i])+1,std::vector<long long>(dmin(siz[rc[o]],totp[i])+1,-0x3f3f3f3f3f3f3f3fll));
			}
		}
	}
	auto ans=F(1,s,op[1]>2,0,0);
	if(ans<0)puts("No solution.");
		else printf("%lld\n",ans);
	return 0;
}