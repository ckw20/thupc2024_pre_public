#include <iostream>
#include <random>
#include <chrono>



int main(int argc, char* argv[]) {
	int N = atoi(argv[1]);
	int p = atoi(argv[2]);

	std::ios::sync_with_stdio(false);

	std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int> dist(0, 100);

	std::cout << N << '\n';

	for (int rep = 0; rep != N; ++rep) {
		std::cout << (dist(rng) <= p);
	}
	std::cout << '\n';

	return 0;
}
