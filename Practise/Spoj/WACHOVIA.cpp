#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int dp[10005];
int w[10005],v[10005];
int main(){
        int t;scanf("%d",&t);
        while(t--){
                int k,n;
                scanf("%d%d",&k,&n);
                fill(dp,dp+10005,0);
                for(int i=0;i<n;i++){
                        scanf("%d%d",&w[i],&v[i]);
                }
                for(int i=0;i<n;i++){
                        for(int j=k;j>=0;j--){
                                if(j>=w[i])
                                        dp[j]=max(dp[j],dp[j-w[i]]+v[i]);
                        }
                }
                printf("Hey stupid robber, you can get %d.\n",dp[k]);
        }
	return 0;
}	
