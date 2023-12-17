#include<bits/stdc++.h>
#include"testlib.h"
#define cmin(a,b) (a>(b)?a=(b),1:0)
#define cmax(a,b) (a<(b)?a=(b),1:0)
#define dmin(a,b) ((a)<(b)?(a):(b))
#define dmax(a,b) ((a)>(b)?(a):(b))
namespace io{
	int F(){
		int n=0,F=0;
		char ch;
		while((ch=getchar())!='-'&&(ch<'0'||ch>'9'));
		ch=='-'?F=1:n=ch-'0';
		while((ch=getchar())>='0'&&ch<='9')n=n*10+ch-'0';
		return F?-n:n;
	}
	long long G(){
		long long n=0,F=0;
		char ch;
		while((ch=getchar())!='-'&&(ch<'0'||ch>'9'));
		ch=='-'?F=1:n=ch-'0';
		while((ch=getchar())>='0'&&ch<='9')n=n*10+ch-'0';
		return F?-n:n;
	}
}
int main(){
    int n;
    registerValidation();
    n=inf.readInt(1,5000,"n");
    inf.readChar('\r');// download on windows but run on wsl
    inf.readEoln();
    std::string s=inf.readToken();
    assert(s.length()==n);
    for(char &c: s){
        assert(c=='v'||c=='^');
    }
    inf.readChar('\r');// download on windows but run on wsl
    inf.readEoln();
    inf.readEof();
	return 0;
}