#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=10005;
int arr[N];
ll ops(ll x){
	return x/5+(x%5)/2+((x%5)%2);
}
int main(){
	int n,t;scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			scanf("%d",&arr[i]);
		}
		int mn=*min_element(arr,arr+n);
		ll mn1=INT_MAX;
		ll sum=0;
		for(int i=0;i<=5;i++){
			sum=0;
			for(int j=0;j<n;j++){
				sum+=ops((ll)arr[j]-(ll)(mn-i));
			}
			if(sum<mn1){
				mn1=sum;
			}
		}
		printf("%lld\n",mn1);
	}
	return 0;
}
