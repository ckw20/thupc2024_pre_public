#include <iostream>
#include <vector>
#include <array>
#include <functional>
#include <queue>
using std::cin, std::cout;

const int B = 5;

int main() {
	int n;
	cin >> n;
	std::string s;
	cin >> s;
	while (n % B) {
		++n;
		s += "0";
	}
	std::vector<int> V[1 << B];
	for (int i = 0; i < n / B; ++i) {
		int x = 0;
		for (int j = 0; j < B; ++j)
			x |= (s[i * B + j] - '0') << j;
		V[x].push_back(i);
	}
	int M = 0;
	std::vector<std::array<int, 3>> ans;
	std::vector<int> siz;
	auto singleton = [&](int v) {
		ans.push_back({1, v, 0});
		{
			siz.push_back(1);
			M += siz.back();
		}
		return (int)ans.size();
	};
	auto coproduct = [&](int i, int j) {
		ans.push_back({2, i, j});
		{
			siz.push_back(siz[i - 1] + siz[j - 1]);
			M += siz.back();
		}
		return (int)ans.size();
	};
	auto translate = [&](int i, int d) {
		ans.push_back({3, i, d});
		{
			siz.push_back(siz[i - 1]);
			M += siz.back();
		}
		return (int)ans.size();
	};
	struct MyCmp {
		std::vector<int> &s;
		MyCmp(std::vector<int> &s_) : s(s_) {}
		bool operator()(int i, int j) {
			return s[i - 1] > s[j - 1];
		}
	};
	MyCmp cmp(siz);
	std::priority_queue<int, std::vector<int>, MyCmp> pq(siz);
	for (int x = 1; x < 1 << B; ++x) {
		if (V[x].empty())
			continue;
		std::vector<int> U;
		for (int j = 0; j < B; ++j)
			if (x >> j & 1)
				U.push_back(j);
		std::function<int(std::vector<int>)> solve = [&](std::vector<int> v) {
			if ((int)v.size() == 1)
				return singleton(v[0]);
			int mid = (int)v.size() / 2;
			std::vector<int> v1(v.begin(), v.begin() + mid), v2(v.begin() + mid, v.end());
			return coproduct(solve(v1), solve(v2));
		};
		std::vector<int> v(V[x]);
		for (int &c : v)
			c = c * B + U[0] + 1;
		int i = solve(v);
		pq.push(i);
		for (int k = 1; k < (int)U.size(); ++k) {
			int i2 = translate(i, U[k] - U[0]);
			pq.push(i2);
		}
	}
	while ((int)pq.size() >= 2) {
		int i = pq.top(); pq.pop();
		int j = pq.top(); pq.pop();
		pq.push(coproduct(i, j));
	}
	cout << (int)ans.size() << '\n';
	for (const auto &[o, x, y] : ans) {
		cout << o << ' ' << x;
		if (o != 1)
			cout << ' ' << y << '\n';
		else
			cout << '\n';
	}
	std::cerr << M << '\n';
	return 0;
}