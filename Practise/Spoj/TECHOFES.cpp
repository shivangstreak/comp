#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int dp[20005];
int cost[25],val[25];
int n,m;
void call_dp(){
        for(int i=0;i<n;i++){
                for(int w=m;w>=0;w--){
                        if(cost[i]<=w){
                                dp[w]=max(dp[w],dp[w-cost[i]]+val[i]);
                        }
                }
        }
}
int main(){
        int t;scanf("%d",&t);
        while(t--){
                fill(dp,dp+20005,0);
                scanf("%d%d",&n,&m);
                for(int i=0;i<n;i++){
                        scanf("%d%d",&cost[i],&val[i]);
                }             
                call_dp();
                printf("%d\n",dp[m]);
        }
	return 0;
}	
