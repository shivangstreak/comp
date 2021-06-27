#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
vector<int> g[1005];
bool vis[1005];
int dp[1005][2];
void init(){
      memset(vis,false,sizeof(vis));
      for(int i=0;i<1005;i++){
         for(int j=0;j<2;j++){
            dp[i][j]=-1;
          }
      }
}
int solve(int x,int f){
        int &res=dp[x][f];
        if(res!=-1){
                return res;
        }
        vis[x]=true;
        res=0;
        int len=g[x].size();
        if(f==1){ //include this node x
              res+=1;
              for(int i=0;i<len;i++){
                        int v=g[x][i];
                        if(vis[v]==false){
                                res+=min(solve(v,1),solve(v,0));
                        }
              }
        }
        else{ //do not include this node x
                res=0;
                for(int i=0;i<len;i++){
                        int v=g[x][i];
                        if(vis[v]==false){
                                res+=solve(v,1);
                        }
                }
        }
        vis[x]=false;
        return res;
}
int main(){
        int n,k,d;
        while(true){
                scanf("%d",&n);
                if(n==0)
                        break;
                for(int i=0;i<1005;i++){
                        g[i].clear();
                }
                for(int i=1;i<=n;i++){
                        scanf("%d",&k);
                        while(k--){
                                scanf("%d",&d);
                                g[i].pb(d);
                        }
                }
                init();
                printf("%d\n",max(1,min(solve(1,0),solve(1,1))));
        }
	return 0;
}
