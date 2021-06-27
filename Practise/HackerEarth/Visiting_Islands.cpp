#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e6+5;
vector<int>g[N],g_rev[N],SSC[N],SSC_G[N];
bool vis[N];
int dp[N];
stack<int>S;
int mark;
int parent[N];
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
                SSC_G[l].pb(r);
                if(vis[v]==false){
                        dfsForConnectingSSCs(v);
                }        
        }
}
int solve(int x){
        if(dp[x]!=-1){
                return dp[x];
        }
        int mx=(int)SSC[x].size(),len=SSC_G[x].size();
        for(int i=0;i<len;i++){
                mx=max(mx,(int)SSC[x].size()+solve(SSC_G[x][i]));
        }
        return dp[x]=mx;
}
int main(){
        int n,x,t;scanf("%d",&t);
        while(t--){
                memset(vis,false,sizeof(vis));
                memset(parent,-1,sizeof(parent));
                for(int i=0;i<N;i++){
                        g[i].clear();
                        SSC[i].clear();
                        SSC_G[i].clear();
                        g_rev[i].clear();
                }
                scanf("%d",&n);
                for(int i=0;i<n;i++){
                        scanf("%d",&x);
                        g[i].pb(x);
                        g_rev[x].pb(i);
                }
              //  cout<<"Before stack\n";
                for(int i=0;i<n;i++){
                        if(vis[i]==false){
                                dfsStack(i);
                        }
                }
              //  cout<<"After stack\n";                
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
               // cout<<"YO\n";
                memset(vis,false,sizeof(vis));
                for(int i=0;i<n;i++){
                        if(vis[i]==false){
                             dfsForConnectingSSCs(i);   
                        }
                }
               // cout<<"Come on\n";
                int mx=0,res;
                memset(dp,-1,sizeof(dp));
                for(int i=0;i<mark;i++){
                        int ans=solve(i);
                        if(ans>mx){
                                mx=ans;
                                res=SSC[i][0];    
                        }
                        else if(ans==mx && SSC[i][0]<res){
                                res=SSC[i][0];
                        }
                }
                printf("%d\n",res);
        }
	return 0;
}	


