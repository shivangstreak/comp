#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
ll dp[1005][1005];
int n,m;
const int MOD=1e9+7;
/*
dp[i][j] tells us that number of ways with i games win by Dexter and j by Mandark with condition that after each round in the game Dexter has atleast M times the points that Mandark has
*/
void callDP(){
        for(int i=1;i<=n;i++){
                for(int j=0;j<=n;j++){
                        dp[i][j]=0;
                }
        }
        for(int i=1;i<=n;i++){
                dp[i][0]=1;
                dp[0][i]=0;
        }
        for(int i=1;i<=n;i++){
                for(int j=1;j<=n;j++){
                        if(i>=m*j){
                                dp[i][j]=(dp[i-1][j]+dp[i][j-1])%MOD;
                        }
                }
        }
}
int main(){
        int t;scanf("%d",&t);
        while(t--){
                scanf("%d%d",&n,&m);
                callDP();
                ll ans=0;
                for(int i=0;i<=n;i++){
                        if(n-i>=i*m && n-i>i){
                                ans+=dp[n-i][i]%MOD;
                                ans%=MOD;
                        }
                }
                printf("%lld\n",ans);
        }
        
	return 0;
}	
