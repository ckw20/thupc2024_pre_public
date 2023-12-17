#include"testlib.h"
#include<bits/stdc++.h>
using namespace std;

int n, p[2003];
void operation(){
	int i = ouf.readInt(1, n) , j = ouf.readInt(i, n), k = ouf.readInt(j + 1, n), l = ouf.readInt(k, n);
	rotate(p + i, p + j + 1, p + k); rotate(p + i, p + k, p + l + 1);
}


int main(int argc, char ** argv){
	registerTestlibCmd(argc, argv);
	n = inf.readInt(1, 2000); for(int i = 1 ; i <= n ; ++i) p[i] = inf.readInt(1, n);
	for(int i = 1 ; i <= n ; ++i) for(int j = i + 1 ; j <= n ; ++j) ensuref(p[i] != p[j], "not a permutation");
	int oufstep = ouf.readInt(0, n), ansstep = ans.readInt(0, n);
	if(oufstep > ansstep) quitf(_wa, "Step is not the minimal");
	for(int i = 1 ; i <= oufstep ; ++i) operation();
	for(int i = 1 ; i <= n ; ++i) ensuref(p[i] == i, "permutation not sorted");
	if(oufstep == ansstep) quitf(_ok, "orz U R the sorting master!");
	if(oufstep < ansstep) quitf(_wa, "Better than jury's solution. Please contact the admin!");
	return 0;
}