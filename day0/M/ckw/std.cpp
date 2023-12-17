#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;
char s[210];
int main() {
	gets(s), assert(strlen(s) <= 200);
	if (strncmp(s, "You are right, but ", 19)) printf("Human\n");
	else printf("AI\n");
	return 0;
}