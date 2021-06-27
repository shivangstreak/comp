#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e5+100;
ll dp[N],arr[N];
int main(){
	int t,n;scanf("%d",&t);
	while(t--){
		memset(dp,0,sizeof(dp));
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			scanf("%lld",&arr[i]);
		}
		if(n<=3){
			ll sum=0;
			for(int i=0;i<n;i++)
				sum+=arr[i];
			printf("%lld\n",sum);
			continue;	
		}
		dp[n-1]=arr[n-1];
		dp[n-2]=dp[n-1]+arr[n-2];
		dp[n-3]=dp[n-2]+arr[n-3];				
		for(int i=n-4;i>=0;i--){
			dp[i]=max(dp[i],arr[i]+dp[i+2]);
			dp[i]=max(dp[i],arr[i]+arr[i+1]+dp[i+4]);
			dp[i]=max(dp[i],arr[i]+arr[i+1]+arr[i+2]+dp[i+6]);
		}
		printf("%lld\n",dp[0]);
	}
	return 0;
}
