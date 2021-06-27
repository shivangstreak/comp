#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e5+5;
ll dp[N];
int main(){
	int t,n;scanf("%d",&t);
	ll arr[N],sum[N];
	while(t--){
		scanf("%d",&n);
		for(int i=n-1;i>=0;i--){
			scanf("%lld",&arr[i]);
		}
		sum[0]=arr[0];
		fill(dp,dp+n+1,0);
		for(int i=1;i<n;i++){
			sum[i]=arr[i]+sum[i-1];
		}
		dp[0]=arr[0];
		dp[1]=arr[1]+dp[0];
		dp[2]=arr[2]+dp[1];
		for(int i=3;i<n;i++){
			dp[i]=max(-1ll,sum[i-1]-dp[i-1]+arr[i]);
			dp[i]=max(dp[i],sum[i-2]-dp[i-2]+arr[i]+arr[i-1]);
			dp[i]=max(dp[i],sum[i-3]-dp[i-3]+arr[i]+arr[i-1]+arr[i-2]);
		}
		printf("%lld\n",dp[n-1]);
	}
    return 0;
}
