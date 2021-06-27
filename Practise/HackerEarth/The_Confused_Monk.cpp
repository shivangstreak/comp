#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
ll arr[55];
const int MOD=1e9+7;
ll mod_pow(ll a,ll b){
	ll res=1;
	while(b>0){
		if(b&1){
			res=res*a;
			if(res>MOD){
				res%=MOD;
			}
		}
		a=((a%MOD)*(a%MOD))%MOD;
		b/=2;
	}
	return res;
}
int main(){
	//cout<<MOD<<endl;
	faster;
	int n;cin>>n;
	ll pro=1;
	for(int i=0;i<n;i++){
		cin>>arr[i];
		pro=((pro%MOD)*(arr[i])%MOD)%MOD;
	}
	ll gcd=arr[0];
	for(int i=1;i<n;i++){
		gcd=__gcd(arr[i],gcd);
	}
	cout<<mod_pow(pro,gcd)<<"\n";
	return 0;
}
