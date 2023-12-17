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
string rdm,bc,wj,lin="lin";
int main(){
	
	int l=14,r=20;
	wj="puzzle",bc="stcg";
	//注意，freopen lin。 
	//文件名字叫 wj bc 表示做改动的东西。 
	system("erase lin.in");
	
	for(int i=l;i<=r;i++)
	{
		int re=system(("rename "+wj+to[i]+".in "+lin+".in").c_str());
		if(!re)
		{
			system(bc.c_str());
			system(("rename "+lin+".out "+wj+to[i]+".in").c_str());
			system(("erase "+lin+".in ").c_str());
		}
		else 
			cerr<<i<<" is jumped \n";
	}
	puts("完毕");
	return 0;
}
