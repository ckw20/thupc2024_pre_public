#include <cstdio>
#include <cstring>
using namespace std;
#define Result(_x) ((_x) % 3 == 0 ? 1 : -1)
#define SIZE 5
int state[SIZE][SIZE], pattern[SIZE][SIZE], res[33660000], ph, pw;
int check(int x, int y){
	int marken = 0;
	for (int i = 0; i < ph && i <= x; ++i) {
		for (int j = 0; j < pw && j <= y; ++j) {
			if (pattern[i][j] && x - i + ph <= SIZE && y - j + pw <= SIZE) {
				marken = 1;
				for (int dx = 0; dx < ph && marken; ++dx) {
					for (int dy = 0; dy < pw; ++dy) {
						if (pattern[dx][dy] && state[x - i + dx][y - j + dy] == 0) {
							marken = 0;
							break;
						}
					}
				}
				if (marken) return 1;
			}
		}
	}
	/*
	for (int i = 0; i + ph <= SIZE; ++i) {
		for (int j = 0; j + pw <= SIZE; ++j) {
			marken = 1;
			for (int dx = 0; dx < ph && marken; ++dx) {
				for (int dy = 0; dy < pw; ++dy) {
					if (pattern[dx][dy] && state[i + dx][j + dy] == 0) {
						marken = 0;
						break;
					}
				}
			}
			if (marken) return 1;
		}
	}
	*/
	return 0;
}
int Bob(int step, int s);
int Alice(int step, int s) {
	if (res[s]) return res[s];
	int best = -2, now;
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (state[i][j] == 0) {
				state[i][j] = 1;
				if (check(i, j)) {
					now = Result(step);
				}
				else {
					now = Bob(step + 1, s | 1 << (i * 5 + j));
				}
				state[i][j] = 0;
				if (now > best) {
					best = now;
					if (best == 1) return res[s] = 1;
				}
			}
		}
	}
	return res[s] = best;
}
int Bob(int step, int s) {
	if (res[s]) return res[s];
	int best = 2, now;
	for (int i = 0; i < SIZE; ++i) {
		for (int j = 0; j < SIZE; ++j) {
			if (state[i][j] == 0) {
				state[i][j] = 1;
				if (check(i, j)) {
					now = -Result(step);
				}
				else {
					now = Alice(step + 1, s | 1 << (i * 5 + j));
				}
				state[i][j] = 0;
				if (now < best) {
					best = now;
					if (best == -1) return res[s] = -1;
				}
			}
		}
	}
	return res[s] = best;
}
int main(){
	ph = 1, pw = 2;
	pattern[0][0] = pattern[0][1] = 1;
	printf("++: %d\n", Alice(1, 0));
	
	memset(res, 0, sizeof(res));
	
	ph = 1, pw = 3;
	pattern[0][0] = pattern[0][1] = pattern[0][2] = 1;
	printf("+++: %d\n", Alice(1, 0));
	
	memset(res, 0, sizeof(res));
	
	ph = 2, pw = 2;
	pattern[0][0] = pattern[0][1] = pattern[1][0] = 1;
	pattern[1][1] = 0;
	printf("++\n+ : %d\n", Alice(1, 0));
	
	memset(res, 0, sizeof(res));
	
	ph = 1, pw = 4;
	pattern[0][0] = pattern[0][1] = pattern[0][2] = pattern[0][3] = 1;
	printf("++++: %d\n", Alice(1, 0));
	
	memset(res, 0, sizeof(res));
	
	ph = 2, pw = 2;
	pattern[0][0] = pattern[0][1] = pattern[1][0] = pattern[1][1] = 1;
	printf("++\n++: %d\n", Alice(1, 0));
	
	memset(res, 0, sizeof(res));
	
	ph = 2, pw = 3;
	pattern[0][0] = pattern[0][1] = pattern[0][2] = pattern[1][0] = 1;
	pattern[1][1] = pattern[1][2] = 0;
	printf("+++\n+  : %d\n", Alice(1, 0));
	
	memset(res, 0, sizeof(res));
	
	ph = 2, pw = 3;
	pattern[0][0] = pattern[0][1] = pattern[0][2] = pattern[1][1] = 1;
	pattern[1][0] = pattern[1][2] = 0;
	printf("+++\n + : %d\n", Alice(1, 0));
	
	memset(res, 0, sizeof(res));
	
	ph = 2, pw = 3;
	pattern[0][0] = pattern[0][1] = pattern[0][2] = pattern[1][2] = 1;
	pattern[1][0] = pattern[1][1] = 0;
	printf("+++\n  +: %d\n", Alice(1, 0));
	
	memset(res, 0, sizeof(res));
	
	return 0;
}