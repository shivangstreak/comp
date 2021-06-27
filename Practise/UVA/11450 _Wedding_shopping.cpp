#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
bool dp[250][25];
int price[25][25];
int main(){
	int m,c,t,k,d;scanf("%d",&t);
	while(t--){
		scanf("%d%d",&m,&c);
		for(int i=0;i<c;i++){
			scanf("%d",&k);
			price[i][0]=k;
			for(int j=1;j<=k;j++){
				scanf("%d",&price[i][j]);				
			}
		}
		for(int i=0;i<250;i++){
			for(int j=0;j<25;j++){
				dp[i][j]=false;
			}
		}
		for(int j=1;j<=price[0][0];j++){
			dp[m-price[0][j]][0]=true;
		}
		for(int i=1;i<c;i++){
			for(int sum=0;sum<=m;sum++){
				if(dp[sum][i-1]==true){
					for(int j=1;j<=price[i][0];j++){
						if(sum-price[i][j]>=0){
							dp[sum-price[i][j]][i]=true;
						}	
					}				
				}
			}	
		}
		int i;
		for(i=0;i<=m;i++){
			if(dp[i][c-1]==true){
				break;
			}
		}
		if(i!=m+1){
			printf("%d\n",m-i);
		}
		else{
			printf("no solution\n");
		}
	}
	return 0;
}
