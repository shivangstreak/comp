#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e6+5;
vector<int>g[N];
bool vis[N],Final[N];
vector<ll> Cost[N];
ll dp[N];
ll dfs(int x){
        if(Final[x]==true){
                return 0;
        }
        if(dp[x]!=-1){
                return dp[x];
        }
        int len=g[x].size();
        ll mx=-1;
        for(int i=0;i<len;i++){
                mx=max(2+Cost[x][i]+dfs(g[x][i]),mx);
        }
        return dp[x]=mx;
}
int main(){
        int r,p,a,b;
        scanf("%d%d",&r,&p);
        ll c;
       // memset(vis,false,sizeof(vis));
        memset(Final,true,sizeof(Final));
        memset(dp,-1,sizeof(dp));
        while(p--){
                scanf("%d%d%lld",&a,&b,&c);
                g[a].pb(b);
                Cost[a].pb(c);
                Final[a]=false;
        }        
        ll mx=-1;
        for(int i=1;i<=r;i++){
                if(Final[i]==false){
                        mx=max(mx,dfs(i));       
                }
        }
        printf("%lld\n",mx);
	return 0;
}	


