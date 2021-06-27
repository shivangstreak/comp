#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int Cost[3005][3005];
vector<int>g[3005];
int dist[3005];
void dijkstra(int s){
	priority_queue<II,vector<II>,greater<II>>q;
	int d=0,size,v;
	II top;
	dist[s]=0;
	q.push({dist[s],s});
	while(q.empty()==false){
		top=q.top();
		q.pop();
		v=top.second;
		d=top.first;
		if(dist[v]<d){
			continue;
		}
		dist[v]=d;
		size=g[v].size();
		for(int i=0;i<size;i++){
			if(dist[g[v][i]]==-1 || dist[g[v][i]]>dist[v]+Cost[v][g[v][i]]){
				dist[g[v][i]]=dist[v]+Cost[v][g[v][i]];
				q.push({dist[g[v][i]],g[v][i]});
			}
		}
	}
}
int main(){
	int s,a,b,n,m,w,t;scanf("%d",&t);
	while(t--){
		for(int i=0;i<3005;i++){
			dist[i]=-1;
		}
		for(int i=0;i<3005;i++){
			for(int j=0;j<3005;j++){
				Cost[i][j]=-1;
			}
		}
		for(int i=0;i<3005;i++){
			g[i].clear();
		}
		scanf("%d%d",&n,&m);
		while(m--){
			scanf("%d%d%d",&a,&b,&w);
			if(Cost[a][b]==-1){
				g[a].pb(b);
				g[b].pb(a);
				Cost[a][b]=w;
				Cost[b][a]=w;
			}
			else{
				if(Cost[a][b]>w){
					Cost[a][b]=w;
					Cost[b][a]=w;
				}
			}
		}
		scanf("%d",&s);
		dijkstra(s);
		for(int i=1;i<=n;i++){
			if(i==s){
				continue;
			}
			else{
				if(dist[i]==-1){
					printf("-1 ");
				}
				else{
					printf("%d ",dist[i]);
				}
			}
		}
		printf("\n");
	}
	return 0;
}
