#include<bits/stdc++.h>
#define cmin(a,b) ((b)<a?a=(b),1:0)
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
int rad[5555];
struct it{
	short st;
	int bal;
}f[5005][5005];
bool operator <(const it &x, const it &y){
	if(x.st!=y.st)return x.st<y.st;
	return x.bal<y.bal;
}
it operator +(const it &x, int y){
	return (it){x.st+1,x.bal+y};
}
std::vector<int> l[5555],r[5555];
int hq,tq;
int main(){
	int n=io::F();
	scanf("%s",s+1);
	for(int i=1;i<=n;++i){
		for(int j=1;i-j>0&&i+j<=n;++j){
			if(s[i-j]!=s[i+j]){
				rad[i]=j;
			}
			else break;
		}
		for(int j=i-rad[i];j<=i;++j){
			l[j].push_back(i);
		}
		for(int j=i;j<=i+rad[i];++j){
			r[j].push_back(i);
		}
	}
	for(int i=1;i<=n;++i){
		std::reverse(r[i].begin(),r[i].end());
	}
	for(int i=n;i;--i){
		for(int j=i;j<=n;++j){
			f[i][j].st=0x3f3f;
			for(int k: l[i]){
				if(k>i+j>>1)break;
				cmin(f[i][j],f[k+1][j]+(j-k-k+i));
			}
			for(int k: r[j]){
				if(k<=i+j>>1)break;
				cmin(f[i][j],f[i][k-1]+(k-i-j+k));
			}
		}
	}
	printf("%d %d\n",f[1][n].st,f[1][n].bal);
	return 0;
}