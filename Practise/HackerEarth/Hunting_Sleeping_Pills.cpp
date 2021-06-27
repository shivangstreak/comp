#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
vector<int>g[105],g_rev[105];
int pills[105];
bool vis[105];
int a,b,n,m;
stack<int>S;
void dfsStack(int x){
        vis[x]=true;
        int len=g[x].size();
        for(int i=0;i<len;i++){
                if(vis[g[x][i]]==false){
                        dfsStack(g[x][i]);
                }
        }
        S.push(x);
}
void ReverseGraph(){
        int len;
        for(int i=1;i<=n;i++){
                len=g[i].size();
                for(int j=0;j<len;j++){
                        int v=g[i][j];
                        g_rev[v].pb(i);
                }
        }
}
void StronglyConnected(int x,vector<int>&v){
        vis[x]=true;
        int len=g_rev[x].size();
        v.pb(x);
        for(int j=0;j<len;j++){
                int u=g_rev[x][j];
                if(vis[u]==false){
                      StronglyConnected(u,v);  
                }
        }
}
void init(){
        for(int i=0;i<105;i++){
                g[i].clear();
                g_rev[i].clear();
                memset(pills,0,sizeof(pills));
                memset(vis,false,sizeof(vis));
                while(!S.empty()){
                        S.pop();
                }
        }
}
int main(){
        int t;scanf("%d",&t);
        while(t--){
                init();
                int mx=INT_MIN;
                scanf("%d%d",&n,&m);
                for(int i=1;i<=n;i++){
                        scanf("%d",&pills[i]);
                }
                while(m--){
                        scanf("%d%d",&a,&b);
                        a++;b++;
                        g[a].pb(b);
                }
                for(int i=1;i<=n;i++){
                        if(vis[i]==false)
                              dfsStack(i);
                }
                memset(vis,false,sizeof(vis));
                ReverseGraph();
                while(S.empty()==false){
                        int top=S.top();
                        S.pop();
                        if(vis[top]==false){
                                vector<int>Vec;
                                StronglyConnected(top,Vec);
                                int len=Vec.size();
                                int ans=0;
                                for(int i=0;i<len;i++){
                                        ans+=pills[Vec[i]];
                                }
                                mx=max(mx,ans);
                        }
                }
                printf("%d\n",mx);
        }
        
	return 0;
}	


