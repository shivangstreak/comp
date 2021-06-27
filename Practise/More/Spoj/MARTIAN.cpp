#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll dp[505][505],sumL[505][505],sumU[505][505];
int main(){
	int n,m;
	while(true){
		scanf("%d%d",&n,&m);
		if(n==0 && m==0)
			break;
		for(int i=0;i<505;i++){
			for(int j=0;j<505;j++){
				dp[i][j]=-1;
			}
		}			
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				scanf("%d",&sumL[i][j]);
			}
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				scanf("%d",&sumU[i][j]);
			}
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				if(j!=0){
					sumL[i][j]+=sumL[i][j-1];
				}
			}
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				if(i!=0){
					sumU[i][j]+=sumU[i-1][j];
				}
			}
		}
		int i=n-1,j=m-1;
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
					ll tempL=sumL[i][j];
					ll tempU=sumU[i][j];
					if(i>0)
						tempL+=dp[i-1][j];
					if(j>0)
						tempU+=dp[i][j-1];	
					dp[i][j]=max(tempL,tempU);
			}
		}
		/*for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				cout<<dp[i][j]<<" ";
			}
			printf("\n");
		}*/
		printf("%lld\n",dp[n-1][m-1]);
	}
	return 0;
}
