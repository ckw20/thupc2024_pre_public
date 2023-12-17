#include<bits/stdc++.h>
//#pragma gcc optimize(3)
//#define gc getchar()
char buf[100000],*buff = buf + 100000;
#define gc ((buff == buf + 100000 ? (fread(buf,1,100000,stdin),buff = buf) : 0),*(buff++))
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
inline li read(){
	li x = 0;
	int y = 0,c = gc;
	while(c < '0' || c > '9') y = c,c = gc;
	while(c >= '0' && c <= '9') x = x * 10 + c - '0',c = gc;
	return y == '-' ? -x : x;
}
inline string reads(){
	string s = "";
	char c = gc;
	while(c == ' ' || c == '\n' || c == '\r' || c == '\t') c = gc;
	while(!(c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == EOF)) s += c,c = gc;
	return s;
}
inline void prt(li x){
	if(x >= 10) prt(x / 10);
	pc(x % 10 + '0');
}
inline void print(li x){
	if(x < 0) pc('-'),x = -x;
	prt(x);
}
inline void file(char *s){
	char c[50];
	sprintf(c,"%s.in",s);
	freopen(c,"r",stdin);
	sprintf(c,"%s.out",s);
	freopen(c,"w",stdout);
}
li s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline li rd(){
	return srd = (srd * s1 + s2 + rand()) % s3;
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
int input_inst(){
	string s = reads();
	int id = ++cnt;
	a[id].id = id;
	if(s == "SLACKOFF"){
		a[id].type = INST_SLACKOFF;
	}
	else if(s == "MOVE"){
		a[id].type = INST_MOVE;
		a[id].h = read();a[id].x = read();
	}
	else if(s == "SWAP"){
		a[id].type = INST_SWAP;
		a[id].h = read();a[id].x = read();a[id].y = read();
	}
	else if(s == "MIRROR"){
		a[id].type = INST_MIRROR;
		a[id].h = read();a[id].x = read();
	}
	else if(s == "REPLACE"){
		a[id].type = INST_REPLACE;
		a[id].h = read();a[id].x = read();
		a[id].pid = input_inst();
	}
	else if(s == "ACTIVATE"){
		a[id].type = INST_ACTIVATE;
		a[id].h = read();
	}
	else if(s == "TRIGGER"){
		a[id].type = INST_TRIGGER;
		s = reads();s.pop_back();
		if(s == "SLACKOFF") a[id].ptype = INST_SLACKOFF;
		else if(s == "MOVE") a[id].ptype = INST_MOVE;
		else if(s == "SWAP") a[id].ptype = INST_SWAP;
		else if(s == "MIRROR") a[id].ptype = INST_MIRROR;
		else if(s == "REPLACE") a[id].ptype = INST_REPLACE;
		else if(s == "ACTIVATE") a[id].ptype = INST_ACTIVATE;
		else if(s == "TRIGGER") a[id].ptype = INST_TRIGGER;
		a[id].pid = input_inst();
	}
	return id;
}
void output(int x,int y){
	if(a[y].type == INST_SLACKOFF){
		printf("Robot %d slacks off.\n",x);
	} 
	if(a[y].type == INST_MOVE){
		printf("Robot %d moves its %s hand towards Robot %d.\n",
			x,(a[y].h ? "right" : "left"),(b[x].hand[a[y].h] + a[y].x) % n);
	} 
	if(a[y].type == INST_SWAP){
		printf("Robot %d swaps a line of command with Robot %d.\n",
			x,b[x].hand[a[y].h]);
	} 
	if(a[y].type == INST_MIRROR){
		printf("Robot %d modifies a line of command of Robot %d.\n",
			x,b[x].hand[a[y].h]);
	} 
	if(a[y].type == INST_REPLACE){
		printf("Robot %d replaces a line of command of Robot %d.\n",
			x,b[x].hand[a[y].h]);
	} 
	if(a[y].type == INST_ACTIVATE){
		printf("Robot %d activates Robot %d.\n",
			x,b[x].hand[a[y].h]);
	} 
}
void work(int x);
void work_inst(int x,int y,bool is_triggered = 0){
	output(x,y);
	if(++tot == k){
		//cerr<<clock()<<endl;
		exit(0);
	} 
	if(a[y].type == INST_SLACKOFF){} 
	if(a[y].type == INST_MOVE){
		(b[x].hand[a[y].h] += a[y].x) %= n;
	} 
	if(a[y].type == INST_SWAP){
		int qx = b[x].hand[a[y].h];
		if(a[b[qx].in[a[y].x]].type != INST_TRIGGER) --b[qx].num_nt,++b[x].num_nt;
		if(a[b[x].in[a[y].y]].type != INST_TRIGGER) --b[x].num_nt,++b[qx].num_nt;
		swap(b[qx].in[a[y].x],b[x].in[a[y].y]);
	} 
	if(a[y].type == INST_MIRROR){
		int qx = b[x].hand[a[y].h];
		int qid = b[qx].in[a[y].x];
		if(a[qid].type == INST_TRIGGER){
			int qqid = a[qid].pid;
			a[qid].pid = ++cnt;
			a[cnt] = a[qqid];
			a[cnt].h ^= 1;
		}
		else{
			b[qx].in[a[y].x] = ++cnt;
			a[cnt] = a[qid];
			a[cnt].h ^= 1;
		}
	} 
	if(a[y].type == INST_REPLACE){
		int qx = b[x].hand[a[y].h];
		if(a[b[qx].in[a[y].x]].type != INST_TRIGGER) --b[qx].num_nt;
		b[qx].in[a[y].x] = ++cnt;
		a[cnt] = a[a[y].pid];
		if(a[cnt].type != INST_TRIGGER) ++b[qx].num_nt;
	} 
	if(a[y].type == INST_ACTIVATE){
		int qx = b[x].hand[a[y].h];
		work(qx);
	} 
	int qx = b[x].hand[1];
	if(x == qx) return;
	for(int i = 1;i <= m;++i){
		int qid = b[qx].in[i];
		if(a[qid].type == INST_TRIGGER && 
			(a[qid].ptype == a[y].type || 
				(a[qid].ptype == INST_TRIGGER && is_triggered))){
			work_inst(qx,a[qid].pid,1);
			break;
		}
	}
}
void work(int x){
	if(!b[x].num_nt) return;
	for(int i = 1;i <= m;++i){
		int inst = b[x].in[i];
		if(a[inst].type != INST_TRIGGER){
			work_inst(x,inst);
		}
	}
}
int main(){
	srand(time(0));rd();
	//file("");
	n = read();m = read();k = read();
	for(int i = 0;i < n;++i){
		b[i].id = i;b[i].hand[0] = read();b[i].hand[1] = read();
		for(int j = 1;j <= m;++j){
			b[i].in[j] = input_inst();
			if(a[b[i].in[j]].type != INST_TRIGGER) ++b[i].num_nt;
		} 
	}
	for(int nw = 0;;nw = (nw + 1) % n) work(nw);
	//fwrite(bfu,1,bfuu - bfu,stdout);
	//cerr<<clock()<<endl;
	return 0;
}


