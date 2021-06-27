#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
vector<int>g[1005];
int Time;
bool vis[1005];
int disc[1005],low[1005],parent[1005],a,b;
int road[1005][1005];
void bridges(int u){
	vis[u]=true;
	int v;
	Time++;
	disc[u]=Time;
	low[u]=Time;
	int size=g[u].size();
	//cout<<u<<endl;
	for(int i=0;i<size;i++){
		v=g[u][i];
		if(vis[v]==false){
			parent[v]=u;
			bridges(v);
			low[u]=min(low[u],low[v]);
			if(low[v]>disc[u]){ //edge(u,v) is a bridge
				road[u][v]=1;
				road[v][u]=1;
			}
			else if(road[v][u]==0) //This is not a bridge so u can remove  v to u path
				road[u][v]=1;
		}
		else if(v!=parent[u]){
			low[u]=min(low[u],disc[v]);
			if(road[v][u]==0)
				road[u][v]=1;
		}	
	}
}
int main(){
	int t,n,m,k=1;
	while(true){
		cin>>n>>m;
		if(n==0 && m==0)
			break;
		for(int i=0;i<1005;i++){
			g[i].clear();
			disc[i]=0;
			low[i]=0;
			parent[i]=-1;
			vis[i]=false;
		}
		Time=0;
		for(int i=0;i<1005;i++)
			for(int j=0;j<1005;j++)
				road[i][j]=0;
		while(m--){
			cin>>a>>b;
			//cout<<a<<" "<<b<<endl;
			g[a].pb(b);
			g[b].pb(a);
		}
		for(int i=1;i<=n;i++){
			if(vis[i]==false){
				bridges(i);
			}
		}
		printf("%d\n\n",k++);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(road[i][j]==1)
					printf("%d %d\n",i,j);
			}
		}
		printf("#\n");
	}	
	return 0;
}
