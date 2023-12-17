#include <cmath>
#include <cstring>

#include <algorithm>
#include <stack>
#include <bitset>
#include <numeric>
#include <iostream>
#include <iomanip>
#include <vector>
#include <random>
#include <chrono>
#include <string>
#include <set>
#include <queue>
#include <map>
#include <unordered_map>

using namespace std;

const int _ = 500050, OTP = _ * 2;

int N;
char s[_];
int op[OTP], ox[OTP], oy[OTP];

int M;
int create(int x) {
	++M;
	op[M] = 1;
	ox[M] = x;
	return M;
}
int merge(int x, int y) {
	if (x == 0 || y == 0) return x + y;
	++M;
	op[M] = 2;
	ox[M] = x;
	oy[M] = y;
	return M;
}
int add(int x, int y) {
	if (x == 0) return 0;
	++M;
	op[M] = 3;
	ox[M] = x;
	oy[M] = y;
	return M;
}

int solve(int L, int R) {
	if (L == R) {
		if (s[L] == '1') return create(L);
		else return 0;
	}
	int mid = (L + R) >> 1;
	int x = solve(L, mid), y = solve(mid + 1, R);
	return merge(x, y);
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> N >> (s + 1);

	solve(1, N);

	std::cout << M << '\n';
	for (int i = 1; i <= M; ++i) {
		if (op[i] == 1) {
			std::cout << "1 " << ox[i] << '\n';
		} else if (op[i] == 2) {
			std::cout << "2 " << ox[i] << ' ' << oy[i] << '\n';
		} else {
			std::cout << "3 " << ox[i] << ' ' << oy[i] << '\n';
		}
	}

	return 0;
}
