#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
vector<int>g[1005];
int dist[1005];
void bfs(int s){
	queue<int>q;
	q.push(s);
	dist[s]=0;
	while(q.empty()==false){
		int top=q.front();
		q.pop();
		int size=g[top].size();
		for(int i=0;i<size;i++){
			if(dist[g[top][i]]==-1){
				dist[g[top][i]]=dist[top]+1;
				q.push(g[top][i]);
			}
		}
	}
}
int main(){
	int a,b,n,m,t,s;scanf("%d",&t);
	while(t--){
		memset(dist,-1,sizeof(dist));
		scanf("%d%d",&n,&m);
		for(int i=0;i<1005;i++){
			g[i].clear();
		}
		while(m--){
			scanf("%d%d",&a,&b);
			g[a].pb(b);
			g[b].pb(a);
		}
		scanf("%d",&s);
		bfs(s);
		for(int i=1;i<=n;i++){
			if(i==s){
				continue;
			}
			else{
				if(dist[i]==-1){
					printf("-1 ");
				}
				else
				printf("%d ",dist[i]*6);
			}
		}
		printf("\n");
	}
	return 0;
}
