#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int dp[2][2000005];
int val[505],w[505];
int main(){
        int k,n;
        scanf("%d%d",&k,&n);
        for(int i=0;i<n;i++){
                scanf("%d%d",&val[i],&w[i]);
        }
        for(int i=0;i<=n;i++){
                for(int j=0;j<=k;j++){
                        if(i==0 || j==0){
                                dp[i%2][j]=0;
                        }
                        else{
                                if(w[i-1]<=j){
                                   dp[i%2][j]=max(dp[(i-1)%2][j-w[i-1]]+val[i-1],dp[(i-1)%2][j]);
                                }
                                else{
                                        dp[i%2][j]=dp[(i-1)%2][j];
                                }
                        }
                }
        }
        printf("%d\n",dp[n%2][k]);
	return 0;
}	
