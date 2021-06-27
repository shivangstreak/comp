#include<bits/stdc++.h> //bridges
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e5+5;
vector<int> g[N];
bool vis[N];
vector<pair<int,int>>E;
int disc[N],low[N],parent[N];
int Time;
map<II,bool>mymap;
void Art(int u){
        vis[u]=true;
        disc[u]=low[u]=++Time;
        int len=g[u].size();
        for(int i=0;i<len;i++){
                int v=g[u][i];
                if(vis[v]==false){
                        parent[v]=u;
                        Art(v);
                        if(low[v]>disc[u]){
                                mymap[{u,v}]=true;
                                mymap[{v,u}]=true;
                        }
                        low[u]=min(low[u],low[v]);
                }
                else if(v!=parent[u]){
                        low[u]=min(low[u],disc[v]);
                }
        }
}
int main(){
        Time=0;
        int q,n,m,x,y;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=m;i++){
                scanf("%d%d",&x,&y);
                g[x].pb(y);
                g[y].pb(x);
                E.pb({x,y});
        }
        memset(vis,false,sizeof(vis));
        memset(parent,-1,sizeof(parent));
        for(int i=1;i<=n;i++){
                if(vis[i]==false){
                        Art(i);
                }
        }
        scanf("%d",&q);
        while(q--){
                scanf("%d",&m);
                if(mymap[{E[m-1].first,E[m-1].second}]==true){
                        printf("Unhappy\n");        
                }
                else{
                        printf("Happy\n");
                }
        }
	return 0;
}	


