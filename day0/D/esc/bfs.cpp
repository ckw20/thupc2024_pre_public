#include<bits/stdc++.h>
#define cmin(a,b) (a>=(b)?a=(b),1:0)
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
char s[5555];
int r[5555];
short f[5005][5005];
bool vis[5005][5005];
int g[5555][5555];
short ql[12522222];
short qr[12522222];
int hq,tq;
int main(){
	int n=io::F();
	scanf("%s",s+1);
	for(int i=1;i<=n;++i){
		for(int j=1;i-j>0&&i+j<=n;++j){
			if(s[i-j]!=s[i+j]){
				r[i]=j;
			}
			else break;
		}
	}
	ql[tq]=1,qr[tq]=n;
	++tq;
	int ans=0;
	for(;hq<tq;++hq){
		int l=ql[hq],r=qr[hq];
		if(l>r)continue;
		if(ans&&f[l][r]==ans){
			break;
		}
		for(int i=l;i<=r;++i){
			if(l>=i-::r[i]||r<=i+::r[i]){
				int tl,tr;
				if(i<=l+r>>1)tl=i+1,tr=r;
					else tl=l,tr=i-1;
				if(!vis[tl][tr]){
					vis[tl][tr]=1;
					f[tl][tr]=f[l][r]+1;
					g[tl][tr]=g[l][r]+std::abs(i-l-(r-i));
					ql[tq]=tl;
					qr[tq++]=tr;
					if(tl>tr){
						ans=f[tl][tr];
					}
				}
				else if(f[tl][tr]==f[l][r]+1){
					cmin(g[tl][tr],g[l][r]+std::abs(i-l-(r-i)));
				}
			}
		}
	}
	int gans=1e9;
	for(int i=1;i<=n+1;++i){
		if(f[i][i-1]==ans){
			cmin(gans,g[i][i-1]);
		}
	}
	printf("%d %d\n",ans,gans);
	return 0;
}