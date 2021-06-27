#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
	int n;scanf("%d",&n);
	ll c=0;
	int root;
	map<int,ll>M;
	for(int i=0;i<n;i++){
		ll smaller=0,larger=0;
		int d;scanf("%d",&d);
		M[d]=0;
		if(i==0){
			root=d;
			printf("0\n");
			continue;	
		}
		else{
			map<int,ll>:: iterator p=M.find(d);
			map<int,ll>:: iterator p1;
			p1=p;
			if(d>root){
				if(++p!=M.end()){
					larger=(*p).second;
				}
				--p1;
				smaller=(*p1).second;
			}
			else{
				if(p!=M.begin()){
					--p;
					smaller=(*p).second;
				}
				++p1;
				larger=(*p1).second;
			}
			ll val=max(smaller,larger);
			val+=1;
			M[d]=val;
			c+=val;
			printf("%lld\n",c);
		}
	}
	return 0;
}
