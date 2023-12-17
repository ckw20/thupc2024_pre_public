#include<bits/stdc++.h>
#define ll long long
using namespace std;
int read()
{
	char c;
	int w=1;
	while((c=getchar())>'9'||c<'0')if(c=='-')w=-1;
	int ans=c-'0';
	while((c=getchar())>='0'&&c<='9')ans=(ans<<1)+(ans<<3)+c-'0';
	return ans*w;
}
int tt=0;
string to[]={"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","55","56","57","58","59","60","61","62","63","64","65","66","67","68","69","70","71","72","73","74","75","76","77","78","79","80","81","82","83","84","85","86","87","88","89","90","91","92","93","94","95","96","97","98","99","100"};
string rdm,bc,wj;
int main(){
	puts("标程名字");
	bc="std";
//	cin>>bc;
	puts("文件名字(默认.in .out)");
	wj="binary";
//	cin>>wj;
	system("cls");
	puts("范围0~100");
	int l=1,r=36;
//	int l=read(),r=read();
	for(int i=l;i<=r;i++)
	{
		system(("erase "+wj+to[i]+".out").c_str());
		system(("erase "+wj+".in").c_str());
		int re=system(("rename "+wj+to[i]+".in "+wj+".in").c_str());
		if(!re)
		{
			cerr<<i<<"@@\n";
			double st=clock();
			system(bc.c_str());
			double ed=clock();
			cerr<<ed-st<<"ms\n";
			system(bc.c_str());
			system(("rename "+wj+".in "+wj+to[i]+".in").c_str());
			system(("rename "+wj+".out "+wj+to[i]+".out").c_str());
		}
		else 
			cerr<<i<<" is jumped \n";
	}
	puts("完毕");
	freopen("sr-sc_history.in","w",stdout);
	cout<<bc<<" "<<wj<<'\n';
	cout<<l<<" "<<r<<"\n";
	return 0;
}
