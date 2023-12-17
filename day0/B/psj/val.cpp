#include"testlib.h"
#include<bits/stdc++.h>
using namespace std;

const int CASES = 20 , SAMPLE = 1 , _ = 5e5 + 7;
int fa[_]; int find(int x){return fa[x] == x ? x : (fa[x] = find(fa[x]));}

int main(){
	for(int i = 1 ; i <= CASES ; ++i){
		freopen(("../data/" + to_string(i) + ".in").c_str() , "r" , stdin);
		registerValidation();
		int N = inf.readInt(1, 5e5 , "N"); inf.readSpace();
		int K = inf.readInt(1, N, "K"); inf.readEoln();
		for(int i = 1 ; i <= N ; ++i) fa[i] = i;
		for(int i = 1 ; i < N ; ++i){
			int x = inf.readInt(1, N, "x"); inf.readSpace();
			int y = inf.readInt(1, N, "y"); inf.readEoln();
			ensuref(find(x) != find(y), "Not a tree");
			fa[find(x)] = find(y);
		}
		inf.readEof();
		cerr << "Case " << i << " complete" << endl;
		fclose(stdin);
	}
	for(int i = 1 ; i <= SAMPLE ; ++i){
		freopen(("../down/" + to_string(i) + ".in").c_str() , "r" , stdin);
		registerValidation();
		int N = inf.readInt(1, 5e5 , "N"); inf.readSpace();
		int K = inf.readInt(1, N, "K"); inf.readEoln();
		for(int i = 1 ; i <= N ; ++i) fa[i] = i;
		for(int i = 1 ; i < N ; ++i){
			int x = inf.readInt(1, N, "x"); inf.readSpace();
			int y = inf.readInt(1, N, "y"); inf.readEoln();
			ensuref(find(x) != find(y), "Not a tree");
			fa[find(x)] = find(y);
		}
		cerr << "Case " << i << " complete" << endl;
		fclose(stdin);
	}
	return 0;
}