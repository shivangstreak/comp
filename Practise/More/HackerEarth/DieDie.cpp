#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const ll MOD=1e9+7;
ll modular_pow(ll base,ll exp){
	ll res=1;
	while(exp>0){
		if(exp&1){
			res=(res*base);
			if(res>=MOD){
				res%=MOD;
			}
			else if(res<0){
				res+=MOD;
			}
		}
		base=base*base;
		if(base>=MOD){
			base%=MOD;
		}
		else if(base<0){
			base+=MOD;
		}
		exp/=2; //exp>>=1;
	}
	return res;
}
int main(){
	int t;cin>>t;
	ll n;
	while(t--){
		cin>>n;
		cout<<modular_pow(modular_pow(2,n-1),MOD-2)<<"\n";
	}
	return 0;
}
