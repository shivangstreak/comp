#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
vector<int> g[105];
bool vis[105];
int Time;
int low[105],disc[105];
bool isArt[105];
int parent[105];
void Art(int x){
        vis[x]=true;
        int child=0;
        int len=g[x].size();
        low[x]=disc[x]=++Time;
        for(int i=0;i<len;i++){
                int v=g[x][i];
                if(vis[v]==false){
                        child++;
                        parent[v]=x;
                        Art(v);
                        if(parent[x]==-1 && child>1){
                                isArt[x]=true;
                        }
                        if(parent[x]!=-1 && low[v]>=disc[x]){
                                isArt[x]=true;
                        }
                        low[x]=min(low[x],low[v]);                      
                }
                else if(v!=parent[x]){
                        low[x]=min(low[x],disc[v]);
                }
        }
}
int main(){
        Time=0;
        int n,m,x,y;scanf("%d%d",&n,&m);
        for(int i=0;i<m;i++){
                scanf("%d%d",&x,&y);
                g[x].pb(y);
                g[y].pb(x);
        }        
        memset(isArt,false,sizeof(isArt));
        memset(parent,-1,sizeof(parent));
        memset(vis,false,sizeof(vis));
        for(int i=1;i<=n;i++){
                if(vis[i]==false){
                        Art(i);
                }
        }
        int q;
        scanf("%d",&q);
        while(q--){
                scanf("%d",&m);
                if(isArt[m]==true){
                        int temp=g[m].size();
                        printf("Satisfied %d\n",temp);
                }
                else{
                        printf("Not Satisfied\n");
                }        
        }
	return 0;
}	


