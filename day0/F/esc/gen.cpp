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
int main(){
	int no=1;
	char s[222];
	sprintf(s,"%d.in",no);
	freopen(s,"w",stdout);
	int n=100,m=1,k=300000;
	printf("%d %d %d\n",n,m,k);
	for(int i=0;i<n;++i){
		printf("%d %d\n",(i+1)%n,(i+1)%n);
		if(i==0){
			for(int j=1;j<=299999;++j){
				printf("REPLACE %d 1 ",R(0,1));
			}
			printf("MIRROR %d 1\n",R(0,1));
		}
		else{
			puts("SLACKOFF");
		}
	}
	return 0;
}