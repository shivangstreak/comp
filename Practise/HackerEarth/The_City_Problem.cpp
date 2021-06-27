#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int n,m,x,y,t;
stack<int>S;
const int N=1e5+9;
vector<int> g[N],g_rev[N];
bool vis[N];
map<int,int>mymap;
void init(){
        for(int i=0;i<N;i++){
                g[i].clear();
                g_rev[i].clear();
        }
        mymap.clear();
        memset(vis,false,sizeof(vis));
}
void dfsStack(int x){
        vis[x]=true;
        int len=g[x].size();
        for(int i=0;i<len;i++){
                int u=g[x][i];
                if(vis[u]==false){
                        dfsStack(u);
                }
        }
        S.push(x);
}
void SCC(int x,int C){
        vis[x]=true;
        int len=g_rev[x].size();
        mymap[C]++;
        for(int i=0;i<len;i++){
                int u=g_rev[x][i];
                if(vis[u]==false){
                        SCC(u,C);
                }
        }
}
int main(){
        scanf("%d",&t);
        while(t--){
              init();
              scanf("%d%d",&n,&m);
              while(m--){
                scanf("%d%d",&x,&y);
                x++;y++;
                g[x].pb(y);
                g_rev[y].pb(x);
              }
              for(int i=1;i<=n;i++){
                if(vis[i]==false){
                         dfsStack(i); 
                }
              }
              memset(vis,false,sizeof(vis));
              int C=1;
              while(S.empty()==false){
                int top=S.top();
                S.pop();
                if(vis[top]==false){
                        SCC(top,C);
                        C++;
                }
              }
              int ans=0;
              for(int i=1;i<C;i++){
                   if(mymap[i]>1){
                        ans++;
                   }
              }
              printf("%d\n",ans);
        }
	return 0;
}	


