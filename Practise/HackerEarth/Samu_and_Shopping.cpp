#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int node[N][3];
int dp[N][3];
int main(){
	int n,t;scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			for(int j=0;j<3;j++)
				scanf("%d",&node[i][j]);
		}
		dp[0][0]=node[0][0];
		dp[0][1]=node[0][1];
		dp[0][2]=node[0][2];
		for(int i=1;i<n;i++){
			dp[i][0]=node[i][0]+min(dp[i-1][1],dp[i-1][2]);
			dp[i][1]=node[i][1]+min(dp[i-1][0],dp[i-1][2]);
			dp[i][2]=node[i][2]+min(dp[i-1][0],dp[i-1][1]);
		}
		int temp=min(dp[n-1][0],min(dp[n-1][1],dp[n-1][2]));
		printf("%d\n",temp);
	}
	return 0;
}
