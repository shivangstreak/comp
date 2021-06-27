#include<bits/stdc++.h>
using namespace std;
int weight[105],val[105];
int dp[505][105];
int main(){
	int bud,n;
	while(true){
		scanf("%d%d",&bud,&n);
		for(int i=0;i<505;i++){
			for(int j=0;j<105;j++){
				dp[i][j]=0;
			}
		}
		if(bud==0 && n==0){
			break;
		}
		for(int i=0;i<n;i++){
			scanf("%d%d",&weight[i],&val[i]);
		}
		for(int w=0;w<=bud;w++){
			for(int j=0;j<=n;j++){
				if(j==0 || w==0){
					dp[w][j]=0;
				}
				else{
					if(w>=weight[j-1])
						dp[w][j]=max(val[j-1]+dp[w-weight[j-1]][j-1],dp[w][j-1]);
					else
						dp[w][j]=dp[w][j-1];
				}
			}
		}
		int joy=dp[bud][n],totalSum=bud;
		for(int i=bud-1;i>=0;i--){
			if(dp[i][n]==joy){
				totalSum=i;
			}
			else{
				break;
			}
		}
		printf("%d %d\n",totalSum,joy);
	}
	return 0;
}
