#include"testlib.h"

int main(int argc, char* argv[]) {
	registerValidation(argc, argv);
    
    int n = inf.readInt(1, 500000, "n");
    inf.readEoln();

    std::string s = inf.readToken("[0]*1[01]*", "s");
    ensuref(s.length() == n, "string length should be n");
    inf.readEoln();
    inf.readEof();

	return 0;
}