#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <array>
#include <set>
#include <utility>
#include <iterator>
using std::cin, std::set;

#define F(i, a, b) for(int i = a; i <= (b); ++i)

const int MN = 100005;

int N;

#define li (i << 1)
#define ri (li | 1)
const int L = 17;
const int S = 1 << L;
int tr[S * 2];
void Modify(int i, int x) {
	tr[i += S] = x;
	for (int j = 0; i >>= 1, j < L; ++j)
		tr[i] = std::min(tr[li], tr[ri]);
}
int Query(int x) {
	int i = 1;
	for (int j = 0; j < L; ++j)
		i = tr[li] <= x ? li : ri;
	return i - S;
}

std::vector<int> V[MN];

using dat = std::array<int, 3>;
set<dat> st;
std::pair<int, int> Erase(int x, int i) {
	auto it = st.lower_bound({x, 0, 0});
	auto &&d = *it;
	if (d[0] != x)
		return {1, 0};
	int l = (*std::next(it))[1] + 1;
	int r = d[1];
	int j = d[2];
	V[j - r + 1].push_back(x);
	V[i - l + 1].push_back(~x);
	st.erase(it);
	return {l, r};
}
void Insert(int x, int r, int i) {
	auto it = st.lower_bound({x, 0, 0});
	if ((*it)[0] == x)
		Erase(x, i);
	st.insert({x, r, i});
}

int main() {
	cin.sync_with_stdio(false);
	cin.tie(nullptr);
	std::memset(tr, 0x3f, sizeof tr);
	cin >> N;
	F(i, 0, N)
		Modify(i, 0);
	st.insert({N + 1, 0, 0});
	F(i, 1, N) {
		int x;
		cin >> x;
		auto [l, r] = Erase(x, i);
		Modify(x, i);
		for (int p = r; p >= l; ) {
			int y = Query(p - 1);
			int q = tr[y + S];
			Insert(y, p, i);
			p = q;
		}
		Insert(!x, i, i);
	}
	F(i, 0, N)
		Erase(i, N + 1);
	set<int> w;
	F(i, 0, N)
		w.insert(i);
	static int cnt[MN];
	F(i, 1, N) {
		for (int x : V[i]) {
			if (x < 0) {
				if (!--cnt[~x])
					w.insert(~x);
			} else {
				if (!cnt[x]++)
					w.erase(x);
			}
		}
		std::cout << *w.begin() << " \n"[i == N];
	}
	return 0;
}
