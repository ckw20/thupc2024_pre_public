#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
using namespace std;
inline int getn(int a, int b) { return (rand() * 32768 + rand()) % (b - a + 1) + a; }
int main()
{
	FILE *fsd=fopen("seed.txt","r");unsigned int sd,ccc;fscanf(fsd,"%u%u",&sd,&ccc);
	FILE *gsd=fopen("seed.txt","w");sd+=12321,ccc+=1;fprintf(gsd,"%u\n%u\n",sd,ccc);
	freopen("data.in","w",stdout),srand((unsigned int)time(0)+sd);
	
	int n = 1000000; printf("%d\n", n);
	rep (i, 1, n) printf("%d", getn(0, 1));
	printf("\n");

	return 0;
}
