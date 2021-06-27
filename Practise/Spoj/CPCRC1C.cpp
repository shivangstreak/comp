#include<bits/stdc++.h>
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
	while(true){
		scanf("%lld%lld",&a,&b);
		if(a==-1 && b==-1){
			break;
		}
		cout<<sod(b)-sod(a-1)<<"\n";
	}
	return 0;
}
