#include<bits/stdc++.h>
using namespace std;
#define ll long long
int nos(ll i){
	int count=0;
	while(i!=0){
		i=i&(i-1);
		count++;
	}
	return count;
}
int main(){
	int t;cin>>t;
	while(t--){
		ll a,b;cin>>a>>b;
		cout<<nos(a^b)<<"\n";
	}
	return 0;
}
