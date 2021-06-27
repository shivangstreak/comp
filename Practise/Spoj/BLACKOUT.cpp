#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
ll arr[2005][2005];
ll val[1005],cost[1005];
ll dp[1005];
ll len;
int m,n,q,k,l1,l2,r1,r2;
void callDP(){
        for(ll i=0;i<len;i++){
                for(ll j=k;j>=0;j--){
                        if(j>=cost[i]){
                                dp[j]=max(dp[j],dp[j-cost[i]]+val[i]);
                        }
                }
        }        
}
int main(){
        scanf("%d%d%d%d",&m,&n,&q,&k);
        fill(dp,dp+1005,0);
        for(int i=0;i<=m;i++){
                arr[i][0]=0;
        }
        for(int i=0;i<=n;i++){
                arr[0][i]=0;
        }
        for(int i=1;i<=m;i++){
                for(int j=1;j<=n;j++){
                        scanf("%lld",&arr[i][j]);
                        arr[i][j]+=arr[i-1][j]+arr[i][j-1]-arr[i-1][j-1];
                }
        }
        len=0;
        while(q--){
                scanf("%d%d%d%d",&l1,&r1,&l2,&r2);
                val[len]=((ll)(l2-l1+1) * (ll)(r2-r1+1));
                cost[len]=arr[l2][r2]-arr[l1-1][r2]-arr[l2][r1-1]+arr[l1-1][r1-1];
                len++;
        }
        callDP();
        printf("%lld\n",dp[k]);
	return 0;
}	
/*
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

long long sum[2001][2001],cost[1000];
int win[1000];
int memo[1000][1001];

int solve(int pos, int have){
    if(pos == -1) return 0;
    
    int &ret = memo[pos][have];
    
    if(ret == -1){
        ret = solve(pos - 1,have);
        
        if(cost[pos] <= have) ret = max(ret,win[pos] + solve(pos - 1,have - cost[pos]));
    }
    
    return ret;
}

int main(){
    int R,C,Q,K;
    
    scanf("%d %d %d %d",&R,&C,&Q,&K);
    
    for(int i = 0;i < C;++i) sum[0][i] = 0;
    for(int i = 0;i < R;++i) sum[i][0] = 0;
    
    for(int i = 1,x;i <= R;++i){
        for(int j = 1;j <= C;++j){
            scanf("%d",&x);
            
            sum[i][j] = x + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        }
    }
    
    int r1,r2,c1,c2;
    int N = 0;
    
    for(int i = 0;i < Q;++i){
        scanf("%d %d %d %d",&r1,&c1,&r2,&c2);
        
        cost[i] = sum[r2][c2] - sum[r1 - 1][c2] - sum[r2][c1 - 1] + sum[r1 - 1][c1 - 1];
        win[i] = (r2 - r1 + 1) * (c2 - c1 + 1);
    }
    
    memset(memo,-1,sizeof memo);
    
    printf("%d\n",solve(Q - 1,K));
    
    return 0;
}
*/
