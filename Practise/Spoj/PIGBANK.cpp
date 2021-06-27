#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e4+5;
int dp[N];
int val[505],wt[505];
int main(){
	int sum,e,f,n,t;scanf("%d",&t);
	while(t--){
		scanf("%d%d%d",&e,&f,&n);
		sum=f-e;
		fill(dp,dp+N,INT_MAX);
		for(int i=0;i<n;i++){
			scanf("%d%d",&val[i],&wt[i]);
		}
		for(int w=1;w<=sum;w++){
			for(int j=0;j<n;j++){
				if(wt[j]==w){
					dp[w]=min(dp[w],val[j]);
				}
				else{
					if(w>wt[j] && dp[w-wt[j]]!=INT_MAX){
						dp[w]=min(dp[w],val[j]+dp[w-wt[j]]);
					}
				} 
			}
		}
		if(dp[sum]==INT_MAX){
			printf("This is impossible.\n");
		}
		else{
			printf("The minimum amount of money in the piggy-bank is %d.\n",dp[sum]);
		}
	}
	return 0;
}
