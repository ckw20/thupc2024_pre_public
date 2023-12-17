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
int n=R(2,100),m=10,k=300000;
void rndcommand(bool basic=false,bool replace=false){
	int type=std::discrete_distribution<int>({0,10,20,10,100,50,3,10})(gen);
	if(basic){
		type=std::discrete_distribution<int>({0,1,1,3,10,2600})(gen);
	}
	else if(replace){
		type=std::discrete_distribution<int>({0,1,1,3,10,4200,1,500})(gen);
	}
	switch(type){
		case 1:
		puts("SLACKOFF");
		break;
		case 2:
		printf("MOVE %d %d\n",R(0,1),R(1,n-1));
		break;
		case 3:
		printf("SWAP %d %d %d\n",R(0,1),R(1,m),R(1,m));
		break;
		case 4:
		printf("MIRROR %d %d\n",R(0,1),R(1,m));
		break;
		case 5:
		printf("REPLACE %d %d ",R(0,1),R(1,m));
		rndcommand(false,true);
		break;
		case 6:
		printf("ACTIVATE %d\n",R(0,1));
		break;
		case 7:
		printf("TRIGGER %s: ",std::vector<std::string>{"SLACKOFF","MOVE","SWAP","MIRROR","REPLACE","ACTIVATE","TRIGGER"}[std::discrete_distribution<int>({1,1,3,10,12000,0,4000})(gen)].c_str());
		rndcommand(true);
		break;
	}
}
int main(){
	int no=io::F();
	char s[222];
	sprintf(s,"%d.in",no);
	freopen(s,"w",stdout);
	printf("%d %d %d\n",n,m,k);
	for(int i=0;i<n;++i){
		printf("%d %d\n",R(0,n-1),R(0,n-1));
		for(int j=1;j<=m;++j){
			rndcommand();
		}
	}
	return 0;
}