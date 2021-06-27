#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e5+5;
const int MOD=1e9+7;
ll arr[N];
ll modular_pow(ll base,ll exp){
	ll res=1;
	while(exp!=0){
		if(exp&1){
			res*=base;
			res%=MOD;
		}
		exp>>=1;
		base=(base%MOD * base%MOD)%MOD;
	}
	return res;
}
int main(){
	int n,t;scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		ll OR=0;
		for(int i=0;i<n;i++){
			scanf("%lld",&arr[i]);
			OR|=arr[i];
		}
		ll ans=(modular_pow(2,n-1))%MOD;
		printf("%lld\n",(ans%MOD * OR%MOD)%MOD);
	}
	return 0;
}	
