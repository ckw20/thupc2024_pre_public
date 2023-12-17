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
	for(int i=1;i<=n;++i){
		int type=R(0,4);
		switch(type){
			case 0:
			a[i]=0;
			c[i]=R(1,300000000);
			b[i]=c[i]+1+R(1,500000000);
			break;
			case 1:
			a[i]=0;
			b[i]=R(1,300000000);
			c[i]=b[i]-1+R(1,500000000);
			break;
			case 2:
			a[i]=R(2,100000000);
			c[i]=R(1,300000000);
			b[i]=0;
			break;
			case 3:
			a[i]=0;
			c[i]=R(1,300000000);
			b[i]=0;
			break;
			case 4:
			a[i]=0;
			c[i]=R(1,300000000);
			b[i]=1;
			break;
		}
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