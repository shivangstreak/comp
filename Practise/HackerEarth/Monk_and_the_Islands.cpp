#include<bits/stdc++.h>
using namespace std;
vector<int>g[100005];
bool vis[100005];
int n;
void bfs(int i){
	queue<pair<int,int>>q;
	q.push(make_pair(i,0));
	while(q.empty()==false){
		pair<int,int> top=q.front();
		q.pop();
		vis[top.first]=true;
		if(top.first==n){
			cout<<top.second<<"\n";
			return;
		}
		for(auto x:g[top.first]){
			if(vis[x]==false){
				q.push(make_pair(x,top.second+1));
			}
		}
	}
}
int main(){
	int t,m,a,b;scanf("%d",&t);
	while(t--){
		memset(vis,false,sizeof(vis));
		for(int i=0;i<100005;i++){
			g[i].clear();
		}
		scanf("%d%d",&n,&m);
		while(m--){
			scanf("%d%d",&a,&b);
			g[a].push_back(b);
			g[b].push_back(a);
		}
		bfs(1);
	}
	return 0;
}
