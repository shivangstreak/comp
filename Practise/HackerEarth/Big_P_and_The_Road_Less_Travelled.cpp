#include<bits/stdc++.h> // How many ways to reach top of mountain i.e n from start 1
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
vector<int>g[10005];
ll c;
int n,x,y;
bool vis[10005];
int dp[10005];
ll dfs(int x){
        if(x==n){
             return 1;
        }
        if(vis[x]==true){
             return dp[x];
        }
        vis[x]=true;
        int len=g[x].size();
        ll ans=0;
        for(int i=0;i<len;i++){
             ans+=dfs(g[x][i]);
        }
        dp[x]=ans;
        return ans;
}
int main(){
        scanf("%d",&n);
        while(true){
                scanf("%d%d",&x,&y);
                if(x==0 &&y==0)
                        break;
                g[x].pb(y);        
        }
        c=dfs(1);
        printf("%lld\n",c);
	return 0;
}	


