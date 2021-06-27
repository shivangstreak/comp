#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e5+5;
vector<int>g[N];
int parent[N],disc[N],low[N];
bool vis[N];
int Time,ANS;
set<int>S;
void ART(int x){
        disc[x]=low[x]=++Time;
        vis[x]=true;
        int len=g[x].size();
        int child=0;
        for(int i=0;i<len;i++){
                int v=g[x][i];
                if(vis[v]==false){
                        parent[v]=x;
                        child++;
                        ART(v);
                        if(parent[x]==-1 && child>1){
                               // ANS++;
                                S.insert(x);
                        }
                        if(parent[x]!=-1 && low[v]>=disc[x]){
                                //ANS++;
                                S.insert(x);
                        }
                        low[x]=min(low[x],low[v]);
                }
                else if(v!=parent[x]){
                        low[x]=min(low[x],disc[v]);
                }
        }
}
void init(){
        memset(parent,-1,sizeof(parent));
        memset(vis,false,sizeof(vis));
        for(int i=0;i<N;i++){
                g[i].clear();
        }
        Time=0;
        ANS=0;
        S.clear();
}
int main(){
        int n,m,a,b;
        while(true){
                scanf("%d%d",&n,&m);
                if(n==0 && m==0){
                        break;
                }
                init();
                while(m--){
                        scanf("%d%d",&a,&b);
                        g[a].pb(b);
                        g[b].pb(a);
                }
                for(int i=1;i<=n;i++){
                        if(vis[i]==false){
                                ART(i);
                        }
                }
                ANS=S.size();
                printf("%d\n",ANS);
        }
	return 0;
}	


