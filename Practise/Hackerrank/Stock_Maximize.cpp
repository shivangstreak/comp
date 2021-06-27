#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N= 50005;
int arr[N];
int main(){
	int n,t;scanf("%d",&t);
	ll mx;
	while(t--){
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			scanf("%d",&arr[i]);
		}
		ll sum=0;
		mx=arr[n-1];
		for(int i=n-2;i>=0;i--){
			if(mx>arr[i]){
				sum+=(ll)(mx-arr[i]);
			}
			else{
				mx=arr[i];
			}
		}
		printf("%lld\n",sum);
	}
	return 0;
}
