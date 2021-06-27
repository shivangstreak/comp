#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e5+5;
vector<int>g[N],g_rev[N],SSC[N];
bool vis[N];
int dp[N];
stack<int>S;
int mark;
int parent[N];
set<int>SET;
map<int,int>out;
void dfsStack(int x){
        vis[x]=true;
        int len=g[x].size();
        for(int i=0;i<len;i++){
                if(vis[g[x][i]]==false)
                      dfsStack(g[x][i]);
        }
        S.push(x);
}
void SSCDfs(int x){
        vis[x]=true;
        int len=g_rev[x].size();
        for(int i=0;i<len;i++){
                if(vis[g_rev[x][i]]==false){
                        SSCDfs(g_rev[x][i]);
                }
        }
        SSC[mark].pb(x);
        parent[x]=mark;
}
void dfsForConnectingSSCs(int x){
        vis[x]=true;
        int len=g[x].size();
        for(int i=0;i<len;i++){
                int v=g[x][i];
                int l=parent[x],r=parent[v];
                if(l==r)
                        continue;
                //SSC_G[l].pb(r);
                SET.insert(l);
                SET.insert(r);
                out[l]++;
                if(vis[v]==false){
                        dfsForConnectingSSCs(v);
                }        
        }
}
int main(){     
                int n,m,a,b;
                memset(vis,false,sizeof(vis));
                memset(parent,-1,sizeof(parent));
                SET.clear();
                out.clear();
                for(int i=0;i<N;i++){
                        g[i].clear();
                        SSC[i].clear();
                        g_rev[i].clear();
                }      
                scanf("%d%d",&n,&m);
                for(int i=0;i<m;i++){
                        scanf("%d%d",&a,&b);
                        g[a].pb(b);
                        g_rev[b].pb(a);
                }   
                for(int i=1;i<=n;i++){
                        if(vis[i]==false){
                                dfsStack(i);
                        }
                }   
                mark=0;
                memset(vis,false,sizeof(vis));
                while(S.empty()==false){
                        int top=S.top();
                        S.pop();
                        if(vis[top]==false){
                                SSCDfs(top);
                                sort(SSC[mark].begin(),SSC[mark].end());
                                mark++;
                        }
                }
                memset(vis,false,sizeof(vis));
                for(int i=1;i<=n;i++){
                        if(vis[i]==false){
                             dfsForConnectingSSCs(i);   
                        }
                }
                int cnt=0;
                set<int>::iterator p;
                p=SET.begin();
                int flag=0;
                int h;
                while(p!=SET.end()){
                        if(out[(*p)]==0){
                                h=*p;
                                cnt++;          
                        }
                        if(cnt>1){
                                flag=1;
                                break;
                        }
                        p++;
                }                  
                if(flag==1 || cnt==0){
                        printf("0\n");
                }                     
                else if(cnt==1){
                         sort(SSC[h].begin(),SSC[h].end());
                         int LEN=SSC[h].size();
                         printf("%d\n",LEN);
                         for(int j=0;j<LEN;j++){
                                printf("%d ",SSC[h][j]);
                         }
                         printf("\n");
                }  
	return 0;
}	


