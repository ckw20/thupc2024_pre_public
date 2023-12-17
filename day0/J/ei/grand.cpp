#include <cmath>

#include <iostream>
#include <random>
#include <chrono>

using namespace std;

int main(int argc, char* argv[]) {
    std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr); std::cout.tie(nullptr);

    int n = atoi(argv[1]);
    std::cout << n << '\n';

    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> uid(0, sqrt(n));

    for (int rep = 1; rep <= n; ++rep)
        std::cout << uid(rng) << " \n"[rep == n];
    
    return 0;
}
