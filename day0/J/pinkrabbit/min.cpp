#include<bits/stdc++.h>
using namespace std;
#define I int
#define F(i,a,b)for(I i=a;i<=(b);++i)
const I S=1<<17;
I n,t[S*2],c[S];
void M(I i,I x){
	for(t[i+=S]=x;i>>=1;)t[i]=min(t[i<<1],t[i<<1|1]);
}
I Q(I x){
	I i=1;
	while(i<S)i=i<<1|(t[i<<1]>x);
	return i-S;
}
vector<I>V[S];
set<array<I,3>>s;
pair<I,I>D(I x,I i){
	auto it=s.lower_bound({x,0,0});
	auto d=*it;
	if(d[0]!=x)return{1,0};
	I l=(*next(it))[1]+1;
	I r=d[1];
	V[d[2]-r+1].push_back(x);
	V[i-l+1].push_back(~x);
	s.erase(it);
	return{l,r};
}
void A(I x,I r,I i){
	auto it=s.lower_bound({x,0,0});
	if((*it)[0]==x)D(x,i);
	s.insert({x,r,i});
}
I main(){
	memset(t,0x3f,sizeof t);
	cin>>n;
	F(i,0,n)M(i,0);
	s.insert({n+1,0,0});
	F(i,1,n){
		I x;
		cin>>x;
		auto[l,r]=D(x,i);
		M(x,i);
		for(I p=r,y,q;p>=l;p=q)q=t[(y=Q(p-1))+S],A(y,p,i);
		A(!x,i,i);
	}
	F(i,0,n)D(i,n+1);
	set<I>w;
	F(i,0,n)w.insert(i);
	F(i,1,n){
		for(I x:V[i])
			if(x<0){
				if(!--c[~x])w.insert(~x);
			}else{
				if(!c[x]++)w.erase(x);
			}
		cout<<*w.begin()<<" \n"[i==n];
	}
}
