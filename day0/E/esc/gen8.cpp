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
int a[355555],b[355555],c[355555];
int main(){
	int no=io::F();
	char s[222];
	sprintf(s,"%d.in",no);
	freopen(s,"w",stdout);
	int n=351493;
	printf("%d\n",n);
	int m=100625;
	int ok=0;
	for(int i=1;i<=m;++i){
		int x;
		do{
			x=std::geometric_distribution<int>(0.1)(gen);
		}
		while(x>n);
		if(!c[x]){
			c[x]=1;
			b[x]+=2;
			if(R(0,9)==0){
				a[x]++;
				++i;
				ok=1;
			}
		}
		else{
			++c[x];
			++b[x];
		}
	}
	assert(ok);
	for(int i=1;i<=n;++i){
		if(c[i]==0&&R(1,3)==1){
			b[i]=1;
		}
		c[i]=R(c[i],1000000000);
	}
	for(int i=1;i<=n;++i){
		int x=R(1,i);
		std::swap(a[x],a[i]);
		std::swap(b[x],b[i]);
		std::swap(c[x],c[i]);
	}
	for(int i=1;i<=n;++i){
		printf("%d%c",a[i]," \n"[i==n]);
	}
	for(int i=1;i<=n;++i){
		printf("%d%c",b[i]," \n"[i==n]);
	}
	for(int i=1;i<=n;++i){
		printf("%d%c",c[i]," \n"[i==n]);
	}
	return 0;
}