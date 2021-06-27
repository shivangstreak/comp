#include<bits/stdc++.h>   // Nice DP!! //My first DP in spoj via a2oj
using namespace std;
#define ll long long
ll dp[150][150][2];
/*
*	dp[i][j][b] :-b can be (1 or 0) 
*	will give me No. of ways to construct a string "str" of length "i" ending with "b" which have AdjBC(str) = j;
*	where AdjBC is the function which was defined in this spoj problem ..Bitchesss!!!
*/

/*
*	  	Recursive definition which i have used:
*		dp[i][j][0]=dp[i-1][j][0] + dp[i-1][j][1];
*		dp[i][j][1]=dp[i-1][j][0] + dp[i-1][j-1][1];
*		Now simply use bottom up DP ....!!! Bitchessss		
*/
int main(){
	int t;scanf("%d",&t);
	for(int q=1;q<=t;q++){
		int o,n,k;scanf("%d%d%d",&o,&n,&k);
		for(int i=0;i<=n;i++){
			for(int j=0;j<=k;j++){
				for(int l=0;l<2;l++){
					dp[i][j][l]=0;
				}
			}
		}
		// base cases!!...No. of ways of constructing a string of length 1 with adjbc()=0 is 1;
		dp[1][0][0]=1;
		dp[1][0][1]=1;
		for(int i=2;i<=n;i++){
			for(int j=0;j<=k;j++){
				dp[i][j][0]=dp[i-1][j][0]+dp[i-1][j][1];
				if(j>0){
					dp[i][j][1]=dp[i-1][j][0]+dp[i-1][j-1][1];
				}
				else{
					dp[i][j][1]=dp[i-1][j][0];
				}
			}
		}
		ll ans=dp[n][k][0]+dp[n][k][1];
		printf("%d %d\n",o,ans);
	}
	return 0;
}
