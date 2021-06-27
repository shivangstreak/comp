#include<bits/stdc++.h>
using namespace std;
const int mx=100005;
vector<int>graph[mx];
bool vis[mx];
void dfs(int i){
	vis[i]=true;
	for(auto x:graph[i]){
		if(vis[x]==false){
			dfs(x);
		}
	}
}
int main(){
	int t;scanf("%d",&t);
	while(t--){
		for(int i=0;i<mx;i++){
			graph[i].clear();
		}
		memset(vis,false,sizeof(vis));
		int a,b,n,e;scanf("%d%d",&n,&e);
		for(int i=0;i<e;i++){
			scanf("%d%d",&a,&b);
			graph[a].push_back(b);
			graph[b].push_back(a);
		}
		int c=0;
		for(int i=0;i<n;i++){
			if(vis[i]==false){
				dfs(i);c++;
			}	
		}
		printf("%d\n",c);
	}
	return 0;
}
