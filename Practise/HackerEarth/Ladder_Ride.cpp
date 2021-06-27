#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const ll MOD=1e9+7;
const int N=1e6+5;
ll dp[N],dp1[N];
int main(){
        ll t,n,curr,k;
        scanf("%lld%lld",&t,&n);
        dp[0]=dp[1]=dp[3]=0;
        dp[2]=dp[5]=dp[4]=1;
        for(int i=6;i<=n;i++){
               dp[i]=(dp[i-2]%MOD + dp[i-5]%MOD)%MOD;
        }
        while(t--){
                scanf("%lld%lld",&curr,&k);
                if(curr<k || k==2 || k==5){
                        printf("%lld\n",dp[curr]);
                }
                else{
                        for(int i=0;i<=k;i++){
                                dp1[i]=dp[i];
                        }
                        dp1[k]=(dp1[k]+1)%MOD;
                        if(k==curr){
                                printf("%lld\n",dp1[curr]);
                                continue;
                        }
                        for(int i=k+1;i<=curr;i++){
                                dp1[i]=(dp1[i-2]%MOD + dp1[i-5]%MOD + dp1[i-k]%MOD)%MOD;
                        }       
                        printf("%lld\n",dp1[curr]); 
                }
        }
	return 0;
}	
