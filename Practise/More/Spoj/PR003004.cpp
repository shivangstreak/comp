#include<bits/stdc++.h> // Similar to CPCRC1C spoj... Finding Digit sum just use below given formula!!!
using namespace std;
#define ll long long
ll sod(ll N){
	if(N<=9){
		return N*(N+1)/2;
	}
	ll i=0;
	ll n=N;
	while(n/10!=0){
		i++;
		n/=10;
	}
	ll p=pow(10,i);
	ll y=((n*i*45*p/10)+(n*(n-1)*p/2)+n*(N%p+1)+sod(N%p));
	return y;
}
int main(){
	ll a,b;
	int t;scanf("%d",&t);
	while(t--){
		cin>>a>>b;
		cout<<sod(b)-sod(a-1)<<"\n";
	}
	return 0;
}
