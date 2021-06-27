#include<bits/stdc++.h>
using namespace std;
vector<int>g[10005];
bool vis[10005];
int n,m;
void dfs(int i){
	vis[i]=true;
	for(auto x:g[i]){
		if(vis[x]==false){
			dfs(x);
		}
	}
}
bool isCyclicUtil(int v,int parent){
	vis[v]=true;
	for(auto x:g[v]){
		if(vis[x]==false){
			if(isCyclicUtil(x,v))
				return true;
		}
		else if(x!=parent){  // If adjacent vertex is visited and is not its parent!! then graph has a cycle!!
			return true;
		}
	}
	return false;
}
bool iscyclic(){
		for(int i=1;i<=n;i++){
			if(vis[i]==false){
				 if (isCyclicUtil(i,-1))
               		                 return true;
			}
		}
		return false;
}
int main(){
	memset(vis,false,sizeof(vis));
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++){
		int a,b;scanf("%d%d",&a,&b);
		g[a].push_back(b);
		g[b].push_back(a);
	}
	if(m!=n-1){
		printf("NO\n");
	}
	else{
		if(iscyclic()){
			printf("NO\n");
		}
		else{
			dfs(1); 
			// check if all the nodes are visited if not then it is not connected so not a tree
			int flag=0;
			for(int i=1;i<=n;i++){
				if(vis[i]==false){
					printf("NO\n");
					flag=1;
					break;
				}
			}
			if(flag==0){
				printf("YES\n");
			}
		}
	}
	return 0;
}
