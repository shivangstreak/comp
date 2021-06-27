#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
	int t;scanf("%d",&t);
	while(t--){
		map<ll,ll>m;
		int n;scanf("%d",&n);
		while(n--){
			ll d;scanf("%lld",&d);
			m[d]++;
		}
		ll sum=0;
		for(auto x:m){
			ll y=x.second;
			sum+=(y*(y-1));
		}
		cout<<sum<<"\n";
	}
	return 0;
}
