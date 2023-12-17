#include <fstream>
#include <random>

std::mt19937 rng(20030811);

std::uniform_int_distribution<int> genp(1, 999999), genn(1, 1e9);

int cnt = 1;

void gendat(int n, int p) {
    std::uniform_int_distribution<int> uid(1, n);
    int l = uid(rng), r = uid(rng);
    if (l > r) std::swap(l, r);

    ++cnt;
    std::string fname = std::to_string(cnt) + ".in";
    std::ofstream fout(fname);

    fout << n << ' ' << (p * 1e-6) << ' ' << l << ' ' << r << '\n';
}

int main() {

    gendat(1, genp(rng));
    gendat(1e9, genp(rng));
    gendat(genn(rng), genp(rng));
    gendat(genn(rng), genp(rng));

    return 0;
}
