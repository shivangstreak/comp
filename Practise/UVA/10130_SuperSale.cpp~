#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int p[1005],w[1005];
int dp[36];
void cal_dp(int n){
	memset(dp,0,sizeof(dp));
	for(int i=0;i<n;i++){
		for(int we=35;we>=0;we--){
			if(w[i]<=we){
				dp[we]=max(dp[we],dp[we-w[i]]+p[i]);
			}
		}
	}
}
int main(){
	int W,n,g,t;scanf("%d",&t);
	ll sum;
	while(t--){
		sum=0;
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			scanf("%d%d",&p[i],&w[i]);
		}
		cal_dp(n);
		scanf("%d",&g);
		for(int i=1;i<=g;i++){
			scanf("%d",&W);
			sum+=dp[W];
		}
		printf("%lld\n",sum);
	}
	return 0;
}
