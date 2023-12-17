#include<bits/stdc++.h>
using namespace std;
int main(){
	string s;
	getline(cin,s);
	cerr<<s<<endl;
	if(s.size() >= 19 && s.substr(0,19) == "You are right, but ")
		puts("AI");
	else puts("Human");
	return 0;
} 
