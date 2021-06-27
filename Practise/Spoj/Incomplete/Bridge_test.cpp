#include<bits/stdc++.h>
using namespace std;
#define DFS_WHITE -1
vector<int>g[100];
int dfs_low[100],dfs_num[100],articulation_vertex[100],dfs_parent[100];
int dfsNumberCounter=0,dfsRoot,rootChildren;
void articulationPointAndBridge(int u) {
	dfs_low[u] = dfs_num[u] = dfsNumberCounter++; // dfs_low[u] <= dfs_num[u]
	for(auto x:g[u]){
		if (dfs_num[x] == DFS_WHITE) { // a tree edge
		dfs_parent[x] = u; // parent of this children is me
		if (u == dfsRoot) // special case
		rootChildren++; // count children of root
		articulationPointAndBridge(x);
		if (dfs_low[x] >= dfs_num[u]) // for articulation point
		articulation_vertex[u] = true; // store this information first
		if (dfs_low[x] > dfs_num[u]) // for bridge
		printf(" Edge (%d, %d) is a bridge\n", u, x);
		dfs_low[u] = min(dfs_low[u], dfs_low[x]); // update dfs_low[u]
		}
		else if (x != dfs_parent[u]) // a back edge and not direct cycle
		dfs_low[u] = min(dfs_low[u], dfs_num[x]); // update dfs_low[u]
	}
}
/*
1 2 1
1 3 2
2 4 2
3 4 1
2 3 1
*/
int main(){
	int n=5;
	g[1].push_back(2);
	g[2].push_back(1);
	g[2].push_back(3);
	g[3].push_back(2);
	g[3].push_back(4);
	g[4].push_back(3);
	g[3].push_back(5);
	g[5].push_back(3);
	g[4].push_back(5);
	g[5].push_back(4);				
	for(int i=1;i<=n;i++){
		if(dfs_num[i]==DFS_WHITE){
			dfsRoot = i; rootChildren = 0;
			articulationPointAndBridge(i);
			articulation_vertex[dfsRoot] = (rootChildren > 1); // special case
		}
	}
	printf("Articulation Points:\n");
	for(int i=0;i<n;i++)
	if (articulation_vertex[i])
		printf(" Vertex %d\n", i);
	return 0;
}

