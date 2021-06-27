#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
ll dp[1005][1005];
const int MOD=1e9+7;
void callDP(){
        for(int i=0;i<1005;i++){
                dp[i][0]=dp[i][i]=1;
                for(int j=1;j<i;j++){
                        dp[i][j]=(dp[i-1][j]%MOD + dp[i-1][j-1]%MOD)%MOD;
                }
        }
}
int main(){
        int t,n,p;scanf("%d",&t);
        callDP();
        while(t--){
                scanf("%d%d",&n,&p);
                ll ans=0;
                for(int i=0;i<=p;i++){
                        ans=(ans%MOD + dp[n][i]%MOD)%MOD;
                }
                printf("%lld\n",ans);
        }
	return 0;
}	


