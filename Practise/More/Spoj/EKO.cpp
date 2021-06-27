#include<bits/stdc++.h>  // Binary Search...!!!
using namespace std;
#define ll long long
#define S(n) scanf("%lld",&n)
int main(){
	ll n,m;S(n);S(m);
	ll h=0;
	ll a[n];
	ll mx=INT_MIN;
	for(int i=0;i<n;i++){
		S(a[i]);
		if(mx<a[i]){
			mx=a[i];
		}
	}
	ll start=0;
	ll end=mx;
	while(start<=end){
		ll mid=(start+end)/2;
		ll c=0;
		for(int i=0;i<n;i++){
			if(a[i]-mid>0){
				c+=a[i]-mid;
			}
		}
		if(c>m){
			start=mid+1;
			if(h<mid){
				h=mid;
			}
		}
		else if(c<m){
			end=mid-1;
		}
		else{
			h=mid;
			break;
		}
	}
	cout<<h<<"\n";
	return 0;
}
