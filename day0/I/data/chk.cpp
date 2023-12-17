#include <random>
#include <chrono>

#include "testlib.h"

using ull = unsigned long long;

const int Threshold = 5e6, _ = 1000005;

const int Mod = 1000000007;

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int Base = std::uniform_int_distribution<int>(0, Mod - 1)(rng);

int min[_], max[_], sum[_], siz[_];

int mpow(int x, int k) {
    if (k < 0) k += Mod - 1;
    int res = 1;
    while (k) {
        if (k & 1) res = (ull) res * x % Mod;
        x = (ull) x * x % Mod;
        k >>= 1;
    }
    return res;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    std::string T = inf.readToken();
    int chkval = 0;
    for (int i = n - 1; i >= 0; --i) {
        chkval = (chkval * (ull) Base + (T[i] - '0')) % Mod;
    }
    chkval = chkval * (ull) Base % Mod;

    int totalCost = 0;

    int m = ouf.readInt(1, 1e6, "m");
    for (int i = 1; i <= m; ++i) {
        int op;
        op = ouf.readInt(1, 3, "op");
        if (op == 1) {
            int x = ouf.readInt(1, n, "x");
            min[i] = max[i] = x;
            siz[i] = 1;
            sum[i] = mpow(Base, x);
        } else if (op == 2) {
            ensuref(i > 1, "No operation before");
            int x = ouf.readInt(1, i - 1, "x");
            int y = ouf.readInt(1, i - 1, "y");
            min[i] = std::min(min[x], min[y]);
            max[i] = std::max(max[x], max[y]);
            siz[i] = siz[x] + siz[y];
            sum[i] = (sum[x] + sum[y]) % Mod;
        } else {
            ensuref(i > 1, "No operation before");
            int x = ouf.readInt(1, i - 1, "x");
            int y = ouf.readInt(-(n - 1), n - 1, "y");
            min[i] = min[x] + y;
            max[i] = max[x] + y;
            siz[i] = siz[x];
            sum[i] = (ull) sum[x] * mpow(Base, y) % Mod;
        }
        ensuref(min[i] >= 1 && max[i] <= n, "Out of range");
        totalCost += siz[i];
        ensuref(totalCost <= Threshold, "Operations total cost exceeds %d", Threshold);
    }

    ensuref(sum[m] == chkval, "Construction not correct");

    ouf.quitf(_ok, "OK total cost = %d", totalCost);

    return 0;
}
