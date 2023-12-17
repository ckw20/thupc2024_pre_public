#include <iostream>
#include <random>
#include <chrono>

std::vector<int> antigen(int N) {
    if (N == 1) return {1};
    std::vector<int> sub = antigen((N + 1) / 2);
    sub.resize(N);
    for (int i = (N + 1) / 2; i < N; ++i) {
        sub[i] = 1 - sub[i - (N + 1) / 2];
    }
    return sub;
}

int main(int argc, char* argv[]) {
	int N = atoi(argv[1]);

    std::cout << N << '\n';
    std::vector<int> S = antigen(N);
    for (int i = (N + 1) / 2; i < N; ++i) S[i] = 1;
    for (int i = 0; i < N; ++i) {
        std::cout << S[i];
    }
    std::cout << '\n';

	return 0;
}
