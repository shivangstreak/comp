#include<bits/stdc++.h> // Stronly Connected Components
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e7+5;
vector<int>g[N],g_rev[N];
vector<int>grp[N];
stack<int>S;
bool vis[N];
int parent[N];
int mark;
void dfs(int x){
        vis[x]=true;
        int len=g[x].size();
        for(int i=0;i<len;i++){
                int v=g[x][i];
                if(vis[v]==false){
                        dfs(v);
                }
        }
        S.push(x);
}
void SSC(int x){
        vis[x]=true;
        grp[mark].pb(x);
        int len=g_rev[x].size();
        parent[x]=mark;
        for(int i=0;i<len;i++){
                int v=g_rev[x][i];
                if(vis[v]==false){
                         SSC(v);
                }
        }
}
int main(){
        int a,b,n,m;scanf("%d%d",&n,&m);
        while(m--){
                scanf("%d%d",&a,&b);
                g[a].pb(b);
                g_rev[b].pb(a);
        }
        memset(vis,false,sizeof(vis));
        for(int i=0;i<n;i++){
                if(vis[i]==false){
                        dfs(i);
                }
        }
        mark=1;
        memset(vis,false,sizeof(vis));        
	while(S.empty()==false){
	        int top=S.top();
	        S.pop();
	        if(vis[top]==false){
	                SSC(top);
	                sort(grp[mark].begin(),grp[mark].end());
	                mark++;
	        }
	}
	for(int i=0;i<n;i++){
	        printf("%d\n",grp[parent[i]][0]);
	}
	return 0;
}	


