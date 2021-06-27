#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int o=1e7;
ll a[o];
int main(){
	ll t;cin>>t;
	while(t--){
		ll n;cin>>n;		
		for(ll i=0;i<n;i++){
			string str;cin>>str;
			cin>>a[i];	
		}
		ll sum=0;
		sort(a,a+n);
		for(ll i=0;i<n;i++){
			sum+=abs(a[i]-(i+1));
		}
		cout<<sum<<"\n";
	}
	return 0;
}
