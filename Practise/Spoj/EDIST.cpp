#include<bits/stdc++.h>
using namespace std;
#define EDIT_COST 1
int dp[2005][2005];
int editDistance(string A,string B){
	int lenA=A.size();
	int lenB=B.size();
	memset(dp,0,sizeof(dp));
	for(int i=0;i<=lenA;i++){
		dp[0][i]=i;
	}
	for(int i=0;i<=lenB;i++){
		dp[i][0]=i;
	}
	dp[0][0]=0;
	for(int i=1;i<=lenA;i++){
		for(int j=1;j<=lenB;j++){
			if(A[i-1]==B[j-1]){
				dp[i][j]=dp[i-1][j-1];
			}
			else{
				dp[i][j]=min(min(dp[i-1][j-1]+1,dp[i-1][j]+EDIT_COST),dp[i][j-1]+EDIT_COST);
			}
		}
	}
	return dp[lenA][lenB];
}
int main(){
	int t;scanf("%d",&t);
	while(t--){
		string A,B;cin>>A>>B;
		cout<<editDistance(A,B)<<"\n";	
	}
	return 0;
}
