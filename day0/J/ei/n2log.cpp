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
int a[_], cnt[_], tmp[_];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr); std::cout.tie(nullptr);

	std::cin >> N;
	for (int i = 1; i <= N; ++i) std::cin >> a[i];

	for (int len = 1; len <= N; ++len) {
		std::set<int> st;
		for (int i = 0; i <= N; ++i) st.insert(i);
		memset(cnt, 0, sizeof(cnt));
		for (int i = 1; i <= N; ++i) {
			if (cnt[a[i]]++ == 0) st.erase(a[i]);
			if (i > len) {
				int v = a[i - len];
				if (--cnt[v] == 0) st.insert(v);
			}
			tmp[i] = *st.begin();
		}
		memset(cnt, 0, sizeof(cnt));
		for (int i = len; i <= N; ++i) cnt[tmp[i]] = 1;
		int mex = 0; while (cnt[mex]) ++mex;
		std::cout << mex << " \n"[len == N];
	}

	return 0;
}
