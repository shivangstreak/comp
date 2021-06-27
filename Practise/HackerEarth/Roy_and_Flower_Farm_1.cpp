#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int dp[105][10005],x[105],y[105];
int n,p,t;
void knapsack(){
        for(int i=0;i<=n;i++){
                for(int j=0;j<=p;j++){
                        if(i==0 || j==0){
                                dp[i][j]=0;
                        }
                        else if(y[i-1]<=j){
                                dp[i][j]=max(dp[i-1][j],x[i-1]+dp[i-1][j-y[i-1]]);
                        }
                        else{
                                dp[i][j]=dp[i-1][j];
                        }
                }
        }
}
int main(){
        scanf("%d",&t);
        while(t--){
                scanf("%d%d",&n,&p);
                for(int i=0;i<n;i++){
                        scanf("%d%d",&x[i],&y[i]);
                }
                knapsack();
                int mn=0;
                for(int i=0;i<=p;i++){
                        if(dp[n][mn]-mn<dp[n][i]-i){
                                mn=i;
                        }
                }
                cout<<mn<<" "<<p+dp[n][mn]-mn<<"\n";
        }
	return 0;
}	


