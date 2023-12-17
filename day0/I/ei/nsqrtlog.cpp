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

const int L = 5;

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

std::vector<int> pos[1 << L];
int solve(int id, int l, int r) {
	if (l == r) return pos[id][l];
	int mid = (l + r) >> 1;
	int x = solve(id, l, mid), y = solve(id, mid + 1, r);
	return merge(x, y);
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> N >> (s + 1);

	for (int i = 1; i <= N; i += L) {
		int mask = 0;
		for (int j = 0; j < L; ++j) {
			if (i + j > N) break;
			mask |= (s[i + j] - '0') << j;
		}
		int lbt = __builtin_ctz(mask);
		if (mask)
			pos[mask].push_back(create(i + lbt));
	}

	std::priority_queue<std::pair<int, int>> pq;

	for (int mask = 1; mask != (1 << L); ++mask) {
		if (pos[mask].empty()) continue;
		int sum = solve(mask, 0, pos[mask].size() - 1);
		pq.emplace(-(int) pos[mask].size(), sum);
		int lbt = __builtin_ctz(mask);
		for (int i = lbt + 1; i != L; ++i) {
			if ((mask >> i) & 1) {
				pq.emplace(-(int) pos[mask].size(), add(sum, i - lbt));
			}
		}
	}
	while (pq.size() > 1) {
		auto x = pq.top(); pq.pop();
		auto y = pq.top(); pq.pop();
		pq.emplace(x.first + y.first, merge(x.second, y.second));
	}
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
