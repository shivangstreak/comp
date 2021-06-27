#include<bits/stdc++.h>
using namespace std;
#define ll unsigned long long
bool isperfectsquare(ll n){
	ll x=sqrt(n);
	return (x*x==n);
}
bool isFibonacci(ll n){
	return (isperfectsquare(5*n*n-4) || isperfectsquare(5*n*n+4));
}
int main(){
	int t;scanf("%d",&t);
	while(t--){
		ll n;cin>>n;
		if(isFibonacci(n)){
			printf("YES\n");
		}
		else{
			printf("NO\n");
		}
	}
	return 0;
}
