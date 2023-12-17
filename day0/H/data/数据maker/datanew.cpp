#include <bits/stdc++.h>
using namespace std;
int cnt = 0;
FILE *o;

//ÌâÄ¿Ãû×Ö¡£ 

const string file_name="std";

int random(int mod)
{   return rand()*rand()%mod+1;
}
long long random_long(int len)
{
	long long tmp =rand()%10;
	for(int i=2;i<=len;i++)
	{	tmp =tmp*10+(rand()%10);
	}
	return tmp;
}
long long random_2_k(int k)
{
	long long tmp = 1;
	for(int i=1;i<=k;i++)
	{
		tmp = tmp*2;
		if(rand()%4 != 0)tmp +=1;
	}
	tmp--;
	return tmp;	
} 
long long random_2_k_1(int k)
{
	long long tmp = 1;
	for(int i=1;i<=k;i++)
		tmp = tmp*2;
	
	tmp--;
	return tmp;	
} 
//map<pair<int,int>,bool>Map;
//if(Map[make_pair(x,y)])
//Map[make_pair(x,y)]=true;

void init() {
	++cnt;
	string s; 
	s="";
	for (int t = cnt; t; t /= 10) s = char(t % 10 + '0') + s;
	s = file_name + s;
	cout << s << endl;
	
	o = fopen((s + ".in").data(), "w");
}

//vector<pair<int, int> > eg;
struct node{int opt,x,y;
}q[100005];
int a[100005];
/*bool cmp(node x,node y) {			//sort cmp
	return x.num<y.num;
}
*/

void output(int n , int Q) {
	fprintf(o, "%d %d\n", n , Q);
	for(int i=1;i<=n;i++){
		fprintf(o, "%d ", a[i]);
	}
	fprintf(o, "\n");

	for(int i=1;i<=Q;i++){
		fprintf(o, "%d %d %d\n", q[i].opt,q[i].x,q[i].y);
	}
	
	/*
	eg.clear();
	for (int i = 1; i <= n; ++i) p[i] = i;
	random_shuffle(p + 1, p + n + 1);
	for (int i = 2; i <= n; ++i) eg.push_back(make_pair(p[i], p[fa[i]]));
	random_shuffle(eg.begin(), eg.end());
	for (int i = 0; i < (int)eg.size(); ++i) {
		if (rarara() & 1) swap(eg[i].first, eg[i].second);
		fprintf(o, "%d %d\n", eg[i].first, eg[i].second);
	}
	*/
}

void runit() {
	string s=""; 
	for (int t = cnt; t; t /= 10) s = char(t % 10 + '0') + s;
	s = file_name + s;
	system((file_name + ".exe < " + s + ".in > " + s + ".out").data());
}

void gen(int n, int Q , int ty) {
	init();
	
	cerr<<"Begin Generate"<<endl;
	
	int ss = 1;
	//fprintf(o, "%d\n", ss);
	while (ss--) {
		if (ty == 0) {
			for(int i=1;i<=n;i++)a[i] = random(100000);
			
			for(int i=1;i<=Q;i++){
				q[i].opt = random(2);
				if(q[i].opt == 1){
					q[i].x = random(n);
					q[i].y = random(100000);
				}
				else {
					q[i].x = random(n/10);
					q[i].y = n - random(n/10);
				}
			}
			
		} else if (ty == 1) {
			
		}
		cerr<<"Begin Output"<<endl;
		output(n , Q);
		cerr<<"Output Finished"<<endl;
	}
	fclose(o);
	runit();
}

int main() {
	
	srand(time(NULL));
	
	for (int i = 1; i <= 1; ++i) gen(20 , 20, 0);//n , Q, type
	for (int i = 2; i <= 5; ++i) gen(100 , 100, 0);
	cnt=5; 
	for (int i = 6; i <= 7; ++i) gen(1000 , 1000, 0);
	for (int i = 8; i <= 10; ++i) gen(100000 , 100000, 0);
	/*for (int i = 13; i <= 16; ++i) gen(262143, 2);
	for (int i = 17; i <= 18; ++i) gen(199995);
	for (int i = 19; i <= 20; ++i) gen(299995);


	cnt=30; 
	gen(500 , 500 , 500 , 500 , 500 , 0);*/
}
