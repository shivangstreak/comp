#include<bits/stdc++.h>
using namespace std;
const int mx=1005;
bool vis[mx];
int A[mx];
vector<int>graph[mx];
vector<int>connected_components;
vector<int>swapable;
void dfs(int i){
	vis[i]=true;
	swapable.push_back(i);
	connected_components.push_back(A[i]);
	for(auto x:graph[i]){
		if(vis[x]==false){
			dfs(x);
		}
	}
}
int main(){
	int n,m,a,b;
	int t;scanf("%d",&t);
	while(t--){
		for(int i=0;i<mx;i++){
			graph[i].clear();
		}
		memset(vis,false,sizeof(vis));
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++){
			scanf("%d",&A[i]);
		}
		while(m--){
			scanf("%d%d",&a,&b);
			graph[a].push_back(b);
			graph[b].push_back(a);
		}
		for(int i=1;i<=n;i++){
			if(vis[i]==false){
				dfs(i);
				sort(connected_components.begin(),connected_components.end());
				sort(swapable.begin(),swapable.end());
				for(int j=0;j<swapable.size();j++){
					A[swapable[j]]=connected_components[j];
				}
				connected_components.clear();
				swapable.clear();
			}
		}
		for(int i=1;i<=n;i++){
			printf("%d ",A[i]);
		}
		printf("\n");
	}
	return 0;
}
