#include<bits/stdc++.h>
using namespace std;
#define ll long long
int C[55];
ll dp[251]; // Number of ways to get total..!!
int main(){
	int sum,n;
	scanf("%d%d",&sum,&n);
	for(int i=0;i<n;i++){
		scanf("%d",&C[i]);
	}
	sort(C,C+n);
	dp[0]=1ll;
	for(int i=0;i<n;i++){
		for(int j=C[i];j<=sum;j++){
			if(dp[j-C[i]]!=0){
				dp[j]+=(ll)dp[j-C[i]];
			}
		}
	}
	printf("%lld\n",dp[sum]);
	return 0;
}

// find the minimum number of coins needed to make N;
/*
memo[0]=0;
int min_coin(int n){
	// base case
	memo[0]=0;
	// fill in memo array 
	for(int i=1;i<=n;i++){
		memo[i]=INF;
		for(int j=0;j<number_denomination;j++){
			if(denomination[j]<=i){
				memo[i]=min(memo[i],memo[i-denomination[j]]+1);			
			}
		}		
	}
	return memo[n];
}
*/
