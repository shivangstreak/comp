#include<bits/stdc++.h>
using namespace std;
#define ll unsigned long long
int main(){
	int t;scanf("%d",&t);
	while(t--){
		int n;scanf("%d",&n);
		ll m;scanf("%llu",&m);
		vector<ll>v;
		ll sum=0;
		for(int i=0;i<n;i++){
			ll d;scanf("%llu",&d);
			v.push_back(d);
		}
		ll i=0;
		sort(v.begin(),v.end(),[](ll x,ll y){return x>y;});
		for(auto x:v){
			sum+=x;
			i++;
			if(sum>=m){
				break;
			}
		}
		if(sum<m){
			printf("-1\n");
		}
		else{
			printf("%llu\n",i);
		}
	}
	return 0;
}
