#include<bits/stdc++.h>   //Dijkstra
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e5+5;
vector<int>Cost[N];
vector<int>g[N];
int dist[N];
void dijkstra(int s){
	priority_queue<II,vector<II>,greater<II>>q;
	int d,v,size;
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
			if(dist[g[v][i]]==-1 || dist[g[v][i]]>dist[v]+Cost[v][i]){
				dist[g[v][i]]=dist[v]+Cost[v][i];
				q.push({dist[g[v][i]],g[v][i]});
			}
		}
	}
}
int main(){
	int s,e,a,b,w,n,m,t;scanf("%d",&t);
	while(t--){
		for(int i=0;i<N;i++){
			g[i].clear();
			Cost[i].clear();
			dist[i]=-1;
		}
		scanf("%d%d%d%d",&n,&m,&s,&e);
		while(m--){
			scanf("%d%d%d",&a,&b,&w);
			g[a].pb(b);
			g[b].pb(a);
			Cost[a].pb(w);
			Cost[b].pb(w);
		}
		dijkstra(s);
		if(dist[e]==-1)
			printf("NONE\n");
		else	
			printf("%d\n",dist[e]);
	}
	return 0;
}
