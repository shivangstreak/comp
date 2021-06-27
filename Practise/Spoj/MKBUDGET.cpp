#include<bits/stdc++.h>
using namespace std;
int dp[25][350],a[25];
int main(){
	int Case=1;
	while(true){
		int l,n,h,m,f;scanf("%d",&n);
		if(n==0){
			break;
		}
		scanf("%d%d%d",&h,&m,&f);
		for(int i=0;i<n;i++){
			scanf("%d",&a[i]);
		}
		for(int i=0;i<25;i++){
			for(int j=0;j<350;j++){
				dp[i][j]=INT_MAX;
			}
		}
		dp[0][a[0]]=a[0]*h+a[0]*m;
		for(int i=0;i<n-1;i++){
			for(int j=0;j<350;j++){
				if(dp[i][j]!=INT_MAX){
					if(a[i+1]>j){
						dp[i+1][a[i+1]]=min(dp[i+1][a[i+1]],dp[i][j]+a[i+1]*m+h*(a[i+1]-j));
					}
					else{ 			//ie j>=a[i+1]
						for(int k=j;k>=a[i+1];k--){
							dp[i+1][k]=min(dp[i+1][k],dp[i][j]+(j-k)*f+m*k);
						}
					}			
				}
			}
		}
		int ans=INT_MAX;
		for(int i=0;i<350;i++){
			ans=min(ans,dp[n-1][i]);
		}
		printf("Case %d, cost = $%d\n",Case,ans);
		Case++;
	}
	return 0;
}
