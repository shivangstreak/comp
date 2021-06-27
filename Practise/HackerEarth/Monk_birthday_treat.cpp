#include<bits/stdc++.h>
using namespace std;
vector<vector<int>>graph;
bool visited[1005];
int c;
void dfs(int i){
	visited[i]=true;
	for(int j=0;j<graph[i].size();j++){
		if(visited[graph[i][j]]==false){
			c++;
			dfs(graph[i][j]);
		}
	}
}
int main(){
	int n,d;scanf("%d%d",&n,&d);
	int ans=INT_MAX;
	graph.resize(n+1);
	while(d--){
		int x,y;
		scanf("%d%d",&x,&y);
		graph[x].push_back(y);
	}
	for(int i=1;i<=n;i++){
		memset(visited,false,sizeof(visited));
		c=1;
		dfs(i);
		ans=min(ans,c);
	}
	printf("%d\n",ans);
	return 0;
}
