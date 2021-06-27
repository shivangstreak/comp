#include<bits/stdc++.h> //dp[l][j] gives no. of valid proper expressions of length l with j more '[' than ']'
using namespace std;    //ans will be dp[2*n][0]
int a[50];
int dp[50][50];
int main(){
	int t;scanf("%d",&t);
	while(t--){
		int n,k,d;scanf("%d%d",&n,&k);
		memset(a,0,sizeof(a));
		for(int i=0;i<k;i++){
			scanf("%d",&d);
			a[d]=1;
		}
		dp[1][1]=1;
		for(int j=2;j<=n;j++){
			dp[1][j]=0;
		}
		for(int l=2;l<=2*n;l++){
			for(int j=0;j<=n;j++){
				if(j==0){
					if(a[l]==1){
						dp[l][j]=0;
					}
					else{
						dp[l][j]=dp[l-1][1];
					}
				}
				else{
					if(a[l]==1){
						dp[l][j]=dp[l-1][j-1];
					}
					else{
						dp[l][j]=dp[l-1][j-1]+dp[l-1][j+1];
					}
				}
			}
		}
		printf("%d\n",dp[2*n][0]);
	}
	return 0;
}
