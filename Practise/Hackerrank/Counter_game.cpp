#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll unsigned long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
bool isPowerOfTwo(ll x){
	return x &&  !( x & (x-1));
}
ll reduce(ll n){
	for(int i=63;i>=0;i--){
		if((n & (1ll <<i))!=0){
			return 1ll << i;
		}
	}
	return 0;
}
int main(){
	//faster;
	int t;cin>>t;
	ll n;
	while(t--){
		cin>>n;
		int f=0;
		if(n==1){
			printf("Richard\n");
			continue;
		}
		while(n!=1){
			if(isPowerOfTwo(n)){
				n=n>>1;
			}
			else{
				n=n-reduce(n);
			}
			f=1-f;
		}
		if(f==0){
			printf("Richard\n");
		}
		else{
			printf("Louise\n");
		}
	}
	return 0;
}	
