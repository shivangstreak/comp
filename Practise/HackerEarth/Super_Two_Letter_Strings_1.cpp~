#include<bits/stdc++.h>  // Working !!!!!
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int MOD=1e9+7,N=1e4+5;;
int n,p;
int dp[N];
int main(){
        int t;scanf("%d",&t);
        while(t--){
                memset(dp,0,sizeof(dp));
                scanf("%d%d",&n,&p);
                dp[0]=1;
                for(int i=1;i<=n;i++){
                        for(int k=0;k<=p-1;k++){
                                if(i-k-1>=0){
                                    dp[i]=(dp[i]%MOD + dp[i-k-1]%MOD)%MOD;
                                }
                        }
                }
                printf("%d\n",dp[n]);
        }
	return 0;
}	


