//You can include .h file like testlib.h here
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

FILE *inFile;
FILE *outFile;
FILE *ansFile;
FILE *scoreFile;
FILE *infoFile;
double score;
bool swap_flag;

void ret(double result, const char* info){
	if(swap_flag)
		fprintf(infoFile, "%s\n", info);	//Arbiter only allow to read EXACTLY one line info, no less and no more, and must BEFORE score
	fprintf(scoreFile, "%.6f\n", result * score);
	if(!swap_flag)
		fprintf(infoFile, "%s\n", info);
	exit(0);
}

int main(int argc, char **argv){
	//You'd better not change this swith block
	switch(argc){
		case 0:		//LOJ
			inFile = fopen("input", "r");
			outFile = fopen("user_out", "r");
			ansFile = fopen("answer", "r");
			scoreFile = stdout;
			infoFile = stderr;
			score = 100;
			break;
		case 4:		//Arbiter
			inFile = fopen(argv[1], "r");
			outFile = fopen(argv[2], "r");
			ansFile = fopen(argv[3], "r");
			scoreFile = infoFile = fopen("/tmp/_eval.score", "w");
			score = 10;
			swap_flag = true;
			break;
		case 5:
			if(strcmp(argv[4], "THUOJ") == 0){	//Tsinghua OJ(OJ for DSA course)
				inFile = fopen(argv[1], "r");
				outFile = fopen(argv[3], "r");
				ansFile = fopen(argv[2], "r");
				scoreFile = stdout;
				infoFile = stdout;
				score = 100;
			}else{								//Tsinsen OJ
				inFile = fopen(argv[1], "r");
				outFile = fopen(argv[2], "r");
				ansFile = fopen(argv[3], "r");
				scoreFile = fopen(argv[4], "w");
				infoFile = fopen("tmp", "w");		//Tsinsen doesn't use this file
				score = 1;
			}
			break;
		case 7:		//Lemon and TUOJ
			inFile = fopen(argv[1], "r");
			outFile = fopen(argv[2], "r");
			ansFile = fopen(argv[3], "r");
			FILE *fs = fopen(argv[4], "r");
			if(fs)
				fscanf(fs, "%lf", &score);		//Current TUOJ
			else
				sscanf(argv[4], "%lf", &score);	//Lemon and future TUOJ
			scoreFile = fopen(argv[5], "w");
			infoFile = fopen(argv[6], "w");
			break;
	}
	long double a, b;
	if(fscanf(outFile, "%Lf", &a) != 1)
		ret(0, "Can\'t read the number.");
	fscanf(ansFile, "%Lf", &b);
	if(fabs(a - b) <= 1e-6 || fabs(a - b) <= b * 1e-6)
		ret(1, "Correct.");
	else {
		if (fabs(a - b) <= b * 0.01) ret(0, "Wrong answer: received difference > 1e-6, but <= 1% (relative diff.).");
		if (fabs(a - b) <= 0.01) ret(0, "Wrong answer: received difference > 1e-6, but <= 0.01 (absolute diff.).");
		if (fabs(a - b) <= b * 0.1) ret(0, "Wrong answer: received difference > 1%, but <= 10% (relative diff.).");
		if (fabs(a - b) <= 0.1) ret(0, "Wrong answer: received difference > 0.01, but <= 0.1 (absolute diff.).");
		ret(0, "Wrong answer: received difference > 10% (relative) and 0.1 (absolute).");
	}
	return 0;
}
