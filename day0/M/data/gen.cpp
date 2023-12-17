#include<bits/stdc++.h>
//#pragma gcc optimize(3)
#define gc getchar()
//char buf[100000],*buff = buf + 100000;
//#define gc ((buff == buf + 100000 ? (fread(buf,1,100000,stdin),buff = buf) : 0),*(buff++))
#define pc putchar
//char bfu[10000000],*bfuu = bfu;
//#define pc(x) (*(bfuu++) = x)
#define li long long
#define uli unsigned li
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define md int mid = l + r >> 1
#define ls q << 1
#define rs q << 1 | 1
#define ln ls,l,mid
#define rn rs,mid + 1,r
using namespace std;
//const int mo = 998244353;
const int mo = 1000000007;
inline li read(){
	li x = 0;
	int y = 0,c = gc;
	while(c < '0' || c > '9') y = c,c = gc;
	while(c >= '0' && c <= '9') x = x * 10 + c - '0',c = gc;
	return y == '-' ? -x : x;
}
inline void prt(li x){
	if(x >= 10) prt(x / 10);
	pc(x % 10 + '0');
}
inline void print(li x){
	if(x < 0) pc('-'),x = -x;
	prt(x);
}
inline void file(int d){
	char c[50];
	sprintf(c,"%d.in",d);
	//freopen(c,"r",stdin);
	//sprintf(c,"%s.out",s);
	freopen(c,"w",stdout);
}
li s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline li rd(){
	return srd = (srd * s1 + s2 + rand()) % s3;
}
int mx[] = {0,9000,35,11,9,9};
void work(int tsd){
	cerr<<tsd<<":"<<endl;
	if(tsd >= 5 && 1){
		file(tsd);
		string s = "";
		if(rd() & 1) s = "You are right, but ";
		int len = rd() % 100 + 50;
		for(int i = 1;i <= len;++i) s += (char)(rd() % (126 - 32 + 1) + 32);
		s += '.';
		cout<<s<<endl;
		fclose(stdout);
	}
	char c[50];
	sprintf(c,"std.exe <%d.in >%d.ans",tsd,tsd);
	system(c);
}
int main(){
	srand(time(0));rd();
	for(int i = 1;i <= 10;++i) work(i);
	//file("");
	//fwrite(bfu,1,bfuu - bfu,stdout);
	//cerr<<clock()<<endl;
	return 0;
}


