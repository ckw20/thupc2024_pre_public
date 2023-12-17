#define FOR_LINUX
#include"testlib.h"
#include<bits/stdc++.h>
using namespace std;

const int CASES = 53 , SAMPLE = 1;

int main(){
	for(int i = 1 ; i <= CASES ; ++i){
		freopen(("../data/" + to_string(i) + ".in").c_str() , "r" , stdin);
		registerValidation();
		int N = inf.readInt(1, 351493 , "N");
		inf.readEoln();
		for(int i = 1 ; i <= N ; ++i){inf.readInt(0, 1e9, "a"); i == N ? void(inf.readEoln()) : void(inf.readSpace());}
		for(int i = 1 ; i <= N ; ++i){inf.readInt(0, 1e9, "b"); i == N ? void(inf.readEoln()) : void(inf.readSpace());}
		for(int i = 1 ; i <= N ; ++i){inf.readInt(0, 1e9, "c"); i == N ? void(inf.readEoln()) : void(inf.readSpace());}
		inf.readEof();
		cerr << "Case " << i << " complete" << endl;
		fclose(stdin);
	}
	for(int i = 1 ; i <= SAMPLE ; ++i){
		freopen(("../down/" + to_string(i) + ".in").c_str() , "r" , stdin);
		int N = inf.readInt(1, 351493 , "N"); inf.readEoln();
		for(int i = 1 ; i <= N ; ++i){inf.readInt(0, 1e9, "a"); i == N ? void(inf.readEoln()) : void(inf.readSpace());}
		for(int i = 1 ; i <= N ; ++i){inf.readInt(0, 1e9, "b"); i == N ? void(inf.readEoln()) : void(inf.readSpace());}
		for(int i = 1 ; i <= N ; ++i){inf.readInt(0, 1e9, "c"); i == N ? void(inf.readEoln()) : void(inf.readSpace());}
		inf.readEof();
		cerr << "Case " << i << " complete" << endl;
		fclose(stdin);
	}
	return 0;
}