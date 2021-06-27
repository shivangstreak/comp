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
		for(int i=0;i<n;i++){
			scanf("%lld",&arr[i]);
		}
		ll sum=0;
		for(int i=31;i>=0;i--){
			for(int k=0;k<n;k++){
				int flag=0;
				for(int j=0;j<32;j++){
					if((arr[k] & 1<<i) & 1<<j){
						flag=1;
						break;
					}
				}
				if(flag==1){
					sum=sum%MOD + (modular_pow(2,i) * modular_pow(2,n-1))%MOD; 
					break;				
				}
			}
		}
		printf("%lld\n",sum%MOD);
	}
	return 0;
}	
