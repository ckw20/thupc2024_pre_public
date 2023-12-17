#include <cstdio>
using namespace std;
char s[9][9];
int main(){
	int T, i, j, count, marken;
	scanf("%d", &T);
	while (T--) {
		count = 0;
		for (i = 0; i < 5; ++i) {
			scanf("%s", s[i]);
			for (j = 0; j < 5; ++j) {
				if (s[i][j] == 'o') ++count;
			}
		}
		if (count == 1) puts("Away");
		else if (count == 2) puts("Far");
		else if (count == 3) puts("Away");
		else {
			marken = 0;
			for (i = 0; i < 2 && marken == 0; ++i) {
				for (j = 0; j < 5; ++j) {
					if (s[i][j] == 'o' && s[i + 1][j] == 'o' && s[i + 2][j] == 'o' && s[i + 3][j] == 'o') {
						// 4 * 1
						marken = 1;
						puts("Away");
						break;
					}
				}
			}
			if (marken) continue;
			for (i = 0; i < 5 && marken == 0; ++i) {
				for (j = 0; j < 2; ++j) {
					if (s[i][j] == 'o' && s[i][j + 1] == 'o' && s[i][j + 2] == 'o' && s[i][j + 3] == 'o') {
						// 1 * 4
						marken = 1;
						puts("Away");
						break;
					}
				}
			}
			if (marken) continue;
			for (i = 0; i < 4 && marken == 0; ++i) {
				for (j = 0; j < 4; ++j) {
					if (s[i][j] == 'o' && s[i][j + 1] == 'o' && s[i + 1][j] == 'o' && s[i + 1][j + 1] == 'o') {
						// 2 * 2
						marken = 1;
						puts("Away");
						break;
					}
				}
			}
			if (marken == 0) puts("Far");
		}
	}
	return 0;
}