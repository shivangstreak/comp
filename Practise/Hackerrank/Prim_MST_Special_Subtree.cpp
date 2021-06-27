#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int Cost[3005][3005];
vector<int>g[3005];
bitset<3005>vis;
ll sum=0;
void primes(int s){
	priority_queue<II,vector<II>,greater<II>>q;
	II top;
	int v,d=0;
	q.push({d,s});
	while(q.empty()==false){
		top=q.top();
		q.pop();
		v=top.second;
		d=top.first;
		if(vis[top.second]==1)
			continue;
		sum+=d;
		vis[top.second]=1;
		//cout<<top.second<<" \n";
		int size=g[v].size();
		for(int i=0;i<size;i++){
			if(vis[g[v][i]]==0){
				q.push({Cost[v][g[v][i]],g[v][i]});
			}
		}	
	}
}
int main(){
	int s,n,m,a,b,w;
	scanf("%d%d",&n,&m);
	vis.reset();
	for(int i=0;i<3005;i++){
		for(int j=0;j<3005;j++){
			Cost[i][j]=-1;
		}
	}
	while(m--){
		scanf("%d%d%d",&a,&b,&w);
		//cout<<a<<" "<<b<<" "<<w<<endl;
		if(Cost[a][b]==-1){
			g[a].pb(b);
			g[b].pb(a);
			Cost[a][b]=w;
			Cost[b][a]=w;
		}
		else{
			if(w<Cost[a][b]){
				Cost[a][b]=w;
				Cost[b][a]=w;
			}
		}
			
	}
	scanf("%d",&s);
	primes(s);
	cout<<sum<<"\n";
	return 0;
}
