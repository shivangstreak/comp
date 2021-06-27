#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int dp[115];
#define MAX 9999999
int main(){
        int t,n;scanf("%d",&t);
        fill(dp,dp+115,MAX);
        dp[10]=1;
        dp[12]=1;
        for(int i=13;i<115;i++){
                dp[i]=min(dp[i],min(dp[i-10]+1,dp[i-12]+1));
        }
        while(t--){
               scanf("%d",&n);
               if(dp[n]>=MAX){
                printf("-1\n");
               }
               else
               printf("%d\n",dp[n]);
        }
	return 0;
}	
