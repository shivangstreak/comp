#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int d[35],v[35];
int dp[35][1005];
int final_d[35],final_v[35];
int t,we,n,Count,indx;
void cal_dp(){
	for(int i=0;i<=n;i++){
		for(int w=0;w<=t;w++){
			if(i==0 || w==0){
				dp[i][w]=0;
			}
			else{
				if(3*we*d[i-1]<=w){
					if(dp[i-1][w]<dp[i-1][w-3*we*d[i-1]]+v[i-1]){
						dp[i][w]=dp[i-1][w-3*we*d[i-1]]+v[i-1];
					}
					else{
						dp[i][w]=dp[i-1][w];
					}
				}
				else{
					dp[i][w]=dp[i-1][w];
				}
			}
		}
	}	
}
void solution(int n,int t){
	if(n<=0)
		return;
	if(dp[n][t]==dp[n-1][t]){
		solution(n-1,t);
	}
	else{
		if(t-3*we*d[n-1]>=0){
			final_d[indx]=d[n-1];
			final_v[indx]=v[n-1];
			indx++;
			t-=3*we*d[n-1];
			solution(n-1,t);
		}
	}
}
int main(){
	int flag=0;
	while(scanf("%d%d",&t,&we)==2){
		if(flag==1)
			printf("\n");
		Count=0;
		indx=0;
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			scanf("%d%d",&d[i],&v[i]);
		}
		cal_dp();
		printf("%d\n",dp[n][t]);
		solution(n,t);
		printf("%d\n",indx);
		for(int i=indx-1;i>=0;i--){
			printf("%d %d\n",final_d[i],final_v[i]);
		}
		flag=1;
	}
	return 0;
}
