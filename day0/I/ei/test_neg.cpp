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

int solve(int L, int R, std::vector<int> S) {
	if ((R - L + 1) & 1) {
		++R; S.push_back(0);
	}
	int cnt = 0, val = 0;
	for (int i = 0; i <= R - L; ++i) if (S[i]) {
		++cnt;
		val = L + i;
	}
	if (cnt == 0) return 0;
	if (cnt == 1) return create(val);
	int len = (R - L + 1) / 2;
	std::vector<int> X(len), Y(len), C(len);
	for (int i = 0; i < len; ++i) {
		C[i] = S[i] && S[i + len];
		X[i] = S[i] - C[i];
		Y[i] = S[i + len] - C[i];
	}
	int x = solve(L, L + len - 1, X);
	int y = solve(L + len, R, Y);
	int c = solve(L + len, R, C);
	c = merge(c, add(c, -len));
	return merge(merge(x, y), c);
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> N >> (s + 1);

	std::vector<int> S(N);
	for (int i = 1; i <= N; ++i)
		S[i - 1] = s[i] - '0';
	solve(1, N, S);

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
