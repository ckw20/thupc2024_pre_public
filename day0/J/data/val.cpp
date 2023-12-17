#include"testlib.h"

int main(int argc, char* argv[]) {
	registerValidation(argc, argv);
    
    int n = inf.readInt(1, 1e5, "n");
    inf.readEoln();

    inf.readInts(n, 0, n, "a");
    inf.readEoln();
    inf.readEof();

	return 0;
}