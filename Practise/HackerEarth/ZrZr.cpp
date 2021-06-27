#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
ll Count(ll n){
	ll ans=0;
	while(n>0){
		ans+=n/5;
		n/=5;
	}
	return ans;
}
int main(){
	faster;
	ll n;
	int t;cin>>t;
	while(t--){
		cin>>n;
		cout<<Count(n)<<"\n";
	}
	return 0;
}
