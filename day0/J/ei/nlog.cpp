#include <cmath>
#include <cstring>

#include <algorithm>
#include <stack>
#include <bitset>
#include <numeric>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <string>
#include <set>
#include <queue>
#include <map>
#include <unordered_map>

typedef unsigned long long ull;

const int _ = 100005;

int N;
int a[_], cnt[_];

std::vector<int> positions[_];
std::vector<std::pair<int, int>> events[_];

std::map<int, int> stair;

namespace SEGT {

int tag[1 << 18], min[1 << 18];

void update(int o) { min[o] = std::min(min[o << 1], min[o << 1 | 1]); }
void apply(int o, int x) { tag[o] += x; min[o] += x; }
void pushdown(int o) {
	apply(o << 1, tag[o]);
	apply(o << 1 | 1, tag[o]);
	tag[o] = 0;
}
void change(int o, int l, int r, int ql, int qr, int x) {
	// std::cerr << "CHANGE " << o << ' ' << l << ' ' << r << ' ' << ql << ' ' << qr << ' ' << x << '\n';
	if (ql <= l && r <= qr) {
		apply(o, x);
		return;
	}
	pushdown(o);
	int mid = (l + r) >> 1;
	if (ql <= mid) change(o << 1, l, mid, ql, qr, x);
	if (qr > mid) change(o << 1 | 1, mid + 1, r, ql, qr, x);
	update(o);
}
int query(int o, int l, int r, int ql, int qr) {
	if (ql <= l && r <= qr) return min[o];
	pushdown(o);
	int mid = (l + r) >> 1;
	int res = std::numeric_limits<int>::max();
	if (ql <= mid) res = std::min(res, query(o << 1, l, mid, ql, qr));
	if (qr > mid) res = std::min(res, query(o << 1 | 1, mid + 1, r, ql, qr));
	return res;
}

}

void insert(int x, int y) {
	// std::cerr << "tring insert " << x << ", " << y << '\n';
	auto it = stair.lower_bound(y);
	if (it->second <= x) return;
	if (it->first != y) --it;
	while (it->second >= x) {
		int delt = it->first - prev(it)->first;
		SEGT::change(1, 1, N, it->second, next(it)->second - 1, -delt);
		stair.erase(it--);
	}
	it = stair.insert(std::make_pair(y, x)).first;
	int delt = y - prev(it)->first;
	// std::cerr << "CHG " << x << ", " << (next(it)->second - 1) << '\n';
	SEGT::change(1, 1, N, x, (++it)->second - 1, delt);
}

int bound_pos(int x) { // first pos < x
	auto it = stair.lower_bound(x);
	return it->second - 1;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr); std::cout.tie(nullptr);

	std::cin >> N;
	for (int i = 1; i <= N; ++i) std::cin >> a[i];

	for (int i = 0; i != N; ++i) positions[i].push_back(0);
	for (int i = 1; i <= N; ++i) positions[a[i]].push_back(i);
	for (int i = 0; i != N; ++i) positions[i].push_back(N + 1);

	for (int i = 0; i <= N + 2; ++i) stair.insert(std::make_pair(i, i));

	for (int i = 0; i != N; ++i) {
		for (int j = 0; j != positions[i].size() - 1; ++j) {
			int l = positions[i][j], r = positions[i][j + 1];
			int pos = bound_pos(r);
			// std::cerr << l << " " << r << ": " << pos << '\n';
			if (pos > l) {
				int u = r - l - 1;
				int d = SEGT::query(1, 1, N, l + 1, pos) + 1;
				events[d].push_back(std::make_pair(i, 1));
				events[u + 1].push_back(std::make_pair(i, -1));
				// std::cerr << i << ": " << d << " ~ " << u << '\n';
			}
			insert(l + 1, r);
		}
	}

	std::set<int> excl;
	for (int i = 0; i <= N; ++i) excl.insert(i);
	for (int i = 1; i <= N; ++i) {
		for (auto &e : events[i]) {
			if (e.second == 1) {
				if (cnt[e.first]++ == 0) excl.erase(e.first);
			} else {
				if (--cnt[e.first] == 0) excl.insert(e.first);
			}
		}
		std::cout << *excl.begin() << " \n"[i == N];
	}

	return 0;
}
