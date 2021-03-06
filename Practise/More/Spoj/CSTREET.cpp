#include<bits/stdc++.h> // Primes Algorithm for MST
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1005;
int cost[N][N];
vector<int>g[N];
ll sum=0;
bitset<N>vis;
void prime(int s){
	priority_queue<II,vector<II>,greater<II>>q;
	q.push({0,s});
	II top;
	while(q.empty()==false){
		top=q.top();
		q.pop();
		if(vis[top.second]==1){
			continue;
		}
		sum+=top.first;
		vis[top.second]=1;
		//cout<<top.second<<" ";
		int size=g[top.second].size();
		for(int i=0;i<size;i++){
			if(vis[g[top.second][i]]==0){
				q.push({cost[top.second][g[top.second][i]],g[top.second][i]});
			}
		}
	}
}
int main(){
	int t,a,b,w,p,m,n;scanf("%d",&t);
	while(t--){
		sum=0ll;
		vis.reset();
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				cost[i][j]=-1;
			}
		}
		for(int i=0;i<N;i++){
			g[i].clear();
		}
		scanf("%d",&p);
		//cout<<p<<endl;
		scanf("%d",&n);
		//cout<<n<<endl;
		scanf("%d",&m);
		//cout<<m<<endl;
		while(m--){
			scanf("%d%d%d",&a,&b,&w);
			//cout<<a<<" "<<b<<" "<<w<<endl;
			if(cost[a][b]==-1){
				cost[a][b]=w;
				cost[b][a]=w;
				g[a].pb(b);
				g[b].pb(a);
			}
			else{
				if(cost[a][b]>w){
					cost[a][b]=w;
					cost[b][a]=w;
				}
			}
		}
		prime(1);
		printf("%lld\n",sum*p);	
	}
	return 0;
}
