#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int dp[1005][1005];
int arr[1005];
int main(){
        int n,k,t;
        scanf("%d",&t);
        for(int tt=1;tt<=t;tt++){
                scanf("%d%d",&n,&k);
                for(int i=0;i<n;i++){
                        scanf("%d",&arr[i]);        
                }
                for(int i=0;i<=n;i++){
                        for(int j=0;j<=k;j++){
                                if(i==0 || j==0){
                                        dp[i][j]=0;
                                }
                                else if(i==1){
                                        if(arr[i-1]<=j){
                                                dp[i][j]=arr[i-1];
                                        }
                                        else{
                                                dp[i][j]=0;
                                        }
                                }
                                else{
                                        if(arr[i-1]<=j){
                                                dp[i][j]=max(arr[i-1]+dp[i-2][j-arr[i-1]],dp[i-1][j]);
                                        }
                                        else{
                                                dp[i][j]=dp[i-1][j];
                                        }
                                }
                        }
                }
                printf("Scenario #%d: %d\n",tt,dp[n][k]);
        }
	return 0;
}	
