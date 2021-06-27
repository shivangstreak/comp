#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e5+5;
vector<int>g[N];
bool vis[N];
int n,m,x,y;
void dfsStack(int x){
        vis[x]=true;
        int len=g[x].size();
        for(int i=0;i<len;i++){
                int v=g[x][i];
                if(vis[v]==false){
                        dfsStack(v);
                }
        }
}
int main(){
        int t;scanf("%d",&t);
        while(t--){
                for(int i=0;i<N;i++){
                        g[i].clear();
                }
	        scanf("%d%d",&n,&m);
	        while(m--){
	                scanf("%d%d",&x,&y);
	                g[x].pb(y);
	        }
                memset(vis,false,sizeof(vis));
                int cnt=0;
	        for(int i=1;i<=n;i++){
	                if(vis[i]==false){
	                        cnt++;
	                        dfsStack(i);       
	                }
	        }
                printf("%d\n",cnt);       
        }
	return 0;
}	


