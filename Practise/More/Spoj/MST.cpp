#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=10005;
int cost[N][N];
vector<int>g[N];
bitset<N>vis;
ll sum=0;
void prime(int s){
	priority_queue<II,vector<II>,greater<II>>q;
	q.push({0,s});
	int v,d;
	II top;
	while(q.empty()==false){
		top=q.top();
		q.pop();
		v=top.second;
		d=top.first;
		if(vis[v]==1)
			continue;
		vis[v]=1;
		sum+=d;
		int size=g[v].size();
		for(int i=0;i<size;i++){
			if(vis[g[v][i]]==0){
				q.push({cost[v][g[v][i]],g[v][i]});
			}
		}
	}
}
int main(){
	vis.reset();
	int a,b,w,m,n;
	scanf("%d%d",&n,&m);
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			cost[i][j]=-1;
		}
	}
	while(m--){
		scanf("%d%d%d",&a,&b,&w);
		//cout<<a<<" "<<b<<" "<<w<<endl;
		if(cost[a][b]==-1){
			g[a].pb(b);
			g[b].pb(a);
			cost[a][b]=w;
			cost[b][a]=w;
		}
		else{
			if(w<cost[a][b]){
				cost[a][b]=w;
				cost[b][a]=w;
			}
		}			
	}
	prime(1);
	printf("%lld\n",sum);
	return 0;
}
