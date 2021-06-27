#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e5+5;
vector<int>g[N],g_rev[N];
bool vis[N];
stack<int>S;
int n,m,x,y;
bool isCorrect[N];
void dfsStack(int x){
        vis[x]=true;
        int len=g[x].size();
        for(int i=0;i<len;i++){
                int v=g[x][i];
                if(vis[v]==false){
                        dfsStack(v);
                }
        }
        S.push(x);
}
void StronglyConnectedDfs(int x,vector<int>&Vec){
        vis[x]=true;
        Vec.pb(x);
        int len=g_rev[x].size();
        for(int i=0;i<len;i++){
                int v=g_rev[x][i];
                if(vis[v]==false){
                         StronglyConnectedDfs(v,Vec);         
                }
        }
}
void ReverseGraph(){
        for(int i=1;i<=n;i++){
                int len=g[i].size();
                for(int j=0;j<len;j++){
                        int v=g[i][j];
                        g_rev[v].pb(i);
                }
        }
}
int main(){
	scanf("%d%d",&n,&m);
	while(m--){
	        scanf("%d%d",&x,&y);
	        g[x].pb(y);
	}
        memset(vis,false,sizeof(vis));
	for(int i=1;i<=n;i++){
	        if(vis[i]==false){
	                dfsStack(i);       
	        }
	}
	memset(isCorrect,false,sizeof(isCorrect));
        memset(vis,false,sizeof(vis));        
        ReverseGraph();
        while(S.empty()==false){
                int top=S.top();
                S.pop();
               // cout<<top<<endl;
                if(vis[top]==false){
                        vector<int>v;
                        StronglyConnectedDfs(top,v);
                        if(v.size()>1){
                                int len=v.size();
                                for(int j=0;j<len;j++){
                                        isCorrect[v[j]]=true;
                                }
                        }
                }
        }
        for(int i=1;i<=n;i++){
                printf("%d ",isCorrect[i]);
        }
        printf("\n");
	return 0;
}	


