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
//const int mo = 1000000007;
int tot_bytes;
inline li read(li l = 0,li r = 1e9){
	li x = 0;
	int y = 0,c = gc;++tot_bytes;
	while(c < '0' || c > '9'){
		assert(y != '-' && (c == ' ' || c == '\n' || c == '\r' || c == '-'));
		y = c;c = gc;++tot_bytes;
	} 
	while(c >= '0' && c <= '9') x = x * 10 + c - '0',c = gc,++tot_bytes;
	assert(c == -1 || c == ' ' || c == '\n' || c == '\r');
	if(y == '-') x *= -1;
	assert(x >= l && x <= r);
	return x;
}
inline string reads(){
	string s = "";
	char c = gc;++tot_bytes;
	while(c == ' ' || c == '\n' || c == '\r' || c == '\t') c = gc,++tot_bytes;
	assert(c != EOF);
	while(!(c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF)) s += c,c = gc,++tot_bytes;
	return s;
}
void end_chk(){
	char c;
	do{
		c = gc,++tot_bytes;
		assert(c == -1 || c == ' ' || c == '\n' || c == '\r');			
	}while(c != -1);
}
int n,m,k,cnt,tot;
struct Inst{
	int type,id;
	int h,x,y;
	int ptype,pid;
}a[2000010];
struct Bot{
	int id,in[15],hand[2];
	int num_nt;
}b[110];
#define INST_SLACKOFF 0
#define INST_MOVE 1
#define INST_SWAP 2
#define INST_MIRROR 3
#define INST_REPLACE 4
#define INST_ACTIVATE 5
#define INST_TRIGGER 6
int input_inst(bool fg = 0){
	string s = reads();
	int id = ++cnt;
	a[id].id = id;
	if(s == "SLACKOFF"){
		a[id].type = INST_SLACKOFF;
	}
	else if(s == "MOVE"){
		a[id].type = INST_MOVE;
		a[id].h = read(0,1);a[id].x = read(1,n - 1);
	}
	else if(s == "SWAP"){
		a[id].type = INST_SWAP;
		a[id].h = read(0,1);a[id].x = read(1,m);a[id].y = read(1,m);
	}
	else if(s == "MIRROR"){
		a[id].type = INST_MIRROR;
		a[id].h = read(0,1);a[id].x = read(1,m);
	}
	else if(s == "REPLACE"){
		a[id].type = INST_REPLACE;
		a[id].h = read(0,1);a[id].x = read(1,m);
		a[id].pid = input_inst();
	}
	else if(s == "ACTIVATE"){
		assert(!fg);
		a[id].type = INST_ACTIVATE;
		a[id].h = read(0,1);
	}
	else if(s == "TRIGGER"){
		assert(!fg);
		a[id].type = INST_TRIGGER;
		s = reads();
		assert(*(s.rbegin()) == ':');
		s.pop_back();
		if(s == "SLACKOFF") a[id].ptype = INST_SLACKOFF;
		else if(s == "MOVE") a[id].ptype = INST_MOVE;
		else if(s == "SWAP") a[id].ptype = INST_SWAP;
		else if(s == "MIRROR") a[id].ptype = INST_MIRROR;
		else if(s == "REPLACE") a[id].ptype = INST_REPLACE;
		else if(s == "ACTIVATE") a[id].ptype = INST_ACTIVATE;
		else if(s == "TRIGGER") a[id].ptype = INST_TRIGGER;
		else assert(0);
		a[id].pid = input_inst(1);
	}
	else assert(0);
	return id;
}
int main(){
	srand(time(0));
	//file("");
	int qwq = 61;
	for(int tsd = 1;tsd <= qwq;++tsd){
		cnt = tot = 0;
		cerr<<tsd<<":"<<endl;
		tot_bytes = 0;
		char ch[50];
		sprintf(ch,"%d.in",tsd);
		freopen(ch,"r",stdin);
		n = read(0,100);m = read(1,10);k = read(1,300000);
		for(int i = 0;i < n;++i){
			b[i].id = i;b[i].hand[0] = read(0,n - 1);b[i].hand[1] = read(0,n - 1);
			for(int j = 1;j <= m;++j){
				b[i].in[j] = input_inst();
			} 
		}
		end_chk();
		cerr<<"tot_bytes: "<<tot_bytes<<endl;
		assert(tot_bytes <= 5 * 1024 * 1024);
		fclose(stdin); 
		freopen("con","r",stdin);
		sprintf(ch,"stdwithleaking.exe <%d.in >std.out",tsd);
		system(ch);
		sprintf(ch,"fc %d.ans std.out",tsd);
		system(ch);
		sprintf(ch,"f.exe <%d.in >std.out",tsd);
		system(ch);
		sprintf(ch,"fc %d.ans std.out",tsd);
		system(ch);
	}
	//fwrite(bfu,1,bfuu - bfu,stdout);
	//cerr<<clock()<<endl;
	return 0;
}


