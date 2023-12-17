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
	int no=3;
	char s[222];
	sprintf(s,"%d.in",no);
	freopen(s,"w",stdout);
	int n=10,m=7,k=300000;
	printf("%d %d %d\n",n,m,k);
	for(int i=0;i<n;++i){
		if(i%2==0)printf("%d %d\n",(i+1)%n,(i+2)%n);
		if(i%2==1)printf("%d %d\n",i,(i+1)%n);
		if(i%2==0){
			if(i==0){
				printf("REPLACE 1 1 ");
				for(int j=1;j<58000/7;++j){
					printf("REPLACE 0 1 ");
				}
			}
			puts("SLACKOFF");
			printf("MIRROR 1 1\n");
			printf("MOVE 1 %d\n",n-2);
			printf("MIRROR 1 1\n");
			printf("SWAP 1 1 6\n");
			puts("SLACKOFF");
			printf("MOVE 1 2\n");
		}
		if(i%2==1){
			puts("SLACKOFF");
			printf("SWAP 0 1 3\n");
			puts("SLACKOFF");
			printf("SWAP 0 1 5\n");
			puts("SLACKOFF");
			printf("SWAP 0 1 3\n");
			printf("REPLACE 0 2 SLACKOFF\n");
		}
	}
	return 0;
}